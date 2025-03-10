// Copyright (c) 2009, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// ---
//
// This file implements the Template Cache used to store templates.

#ifndef TEMPLATE_TEMPLATE_CACHE_H_
#define TEMPLATE_TEMPLATE_CACHE_H_

#include <map>
#include <string>        // for string
#include <utility>       // for pair
#include <vector>        // for vector<>
#include <ctemplate/template_emitter.h>  // for ExpandEmitter, etc
#include <ctemplate/template_enums.h>  // for Strip
#include <ctemplate/template_string.h>
#include <ctemplate/per_expand_data.h>
namespace ctemplate {
class FileStat;
}
class Mutex;
class TemplateCacheUnittest;



namespace ctemplate {

class PerExpandData;
class Template;
class TemplateCachePeer;
class TemplateDictionaryInterface;

// A cache to store parsed templates.
class  TemplateCache {
 public:
  TemplateCache();
  ~TemplateCache();

  // ---- CREATING A TEMPLATE OBJECT -------
  //    LoadTemplate
  //    StringToTemplateCache

  // Attempts to load the template object stored under its filename,
  // into the template cache. It first checks if the object is already
  // in the cache.  Any object retrieved from the cache is then
  // checked to see if its status is marked for "reload if changed."
  // If so, ReloadIfChanged is called on the retrieved object. Returns
  // true if the object is loaded.  Also returns true if the object
  // already exists, and no reload was required.
  //
  // When it fails to retrieve one from the cache, it creates a new
  // template object, passing the filename and 'strip' values to the
  // constructor. (See constructor below for the meaning of the
  // flags.)  If it succeeds in creating an object, including loading
  // and parsing the associated template file, the object is stored in
  // the cache, and the method returns true.
  //
  // If it fails in loading and parsing the template file, either
  // because the file was not found or it contained syntax errors,
  // then the newly created object is deleted and the method returns
  // false.  (NOTE: This description is much longer and less precise
  // and probably harder to understand than the method itself. Read
  // the code.)
  //
  // To enable Auto-Escape on that template, place the corresponding
  // AUTOESCAPE pragma at the top of the template file. The template
  // will then be Auto-Escaped independently of the template it may be
  // included from or the templates it may include.
  //
  // 'Strip' indicates how to handle whitespace when expanding the
  // template.  DO_NOT_STRIP keeps the template exactly as-is.
  // STRIP_BLANK_LINES elides all blank lines in the template.
  // STRIP_WHITESPACE elides all blank lines, and also all whitespace
  // at either the beginning or end of a line.  See template constructor
  // for more details.
  bool LoadTemplate(const TemplateString& filename, Strip strip);

  // Parses the string as a template file (e.g. "Hello {{WORLD}}"),
  // and inserts it into the parsed template cache, so it can later be
  // used by the user. The user specifies a key and a strip, which are
  // later passed in to expand the template.
  // Returns true if the template was successfully parsed and
  // inserted to the template cache, or false otherwise.  In particular,
  // we return false if a string was already cached with the given key.
  // NOTE: to include this template from within another template (via
  // "{{>TEMPLATE_THAT_COMES_FROM_A_STRING}}"), the argument you pass
  // to TemplateDictionary::SetFilename() is the key you used to register
  // the string-template.
  bool StringToTemplateCache(const TemplateString& key,
                             const TemplateString& content,
                             Strip strip);
  bool StringToTemplateCache(const TemplateString& key,
                             const char* content,
                             size_t content_len,
                             Strip strip) {
    return StringToTemplateCache(key,
                                 TemplateString(content, content_len),
                                 strip);
  }

  // ---- EXPANDING A TEMPLATE -------
  //    ExpandWithData
  //    ExpandFrozen

  // This returns false if the expand failed for some reason: filename
  // could not be found on disk (and isn't already in the cache), or
  // the template is mal-formed, or a sub-included template couldn't
  // be found.  Note that even if it returns false, it may have emitted
  // some output to ExpandEmitter, before it noticed the problem.
  bool ExpandWithData(const TemplateString& filename, Strip strip,
                      const TemplateDictionaryInterface *dictionary,
                      PerExpandData* per_expand_data,
                      ExpandEmitter* output);
  bool ExpandWithData(const TemplateString& filename, Strip strip,
                      const TemplateDictionaryInterface* dictionary,
                      PerExpandData* per_expand_data,
                      std::string* output_buffer) {
    if (output_buffer == NULL)  return false;
    StringEmitter e(output_buffer);
    return ExpandWithData(filename, strip, dictionary, per_expand_data, &e);
  }

  // Const version of ExpandWithData, intended for use with frozen
  // caches.  This method returns false if the requested
  // template-filename is not found in the cache, rather than fetching
  // the template from disk and continuing, as ExpandWithData does.
  // (That is why the method can be const.)  Likewise, it will return
  // false, rather than fetch, if any sub-included template filename
  // is not found in the cache.
  // Unfortunately, the only way to enforce this last requirement at
  // the moment is to have the template-cache be Frozen().  So that
  // is a pre-requisite for calling this method.  It may be relaxed
  // in the future (if we rewrite the control flow to pass around the
  // necessary state).
  // Like ExpandWithData(), this may write partial results into output
  // even if it returns false (due to template error or file not found).
  bool ExpandNoLoad(const TemplateString& filename, Strip strip,
                    const TemplateDictionaryInterface *dictionary,
                    PerExpandData* per_expand_data,
                    ExpandEmitter* output) const;
  bool ExpandNoLoad(const TemplateString& filename, Strip strip,
                    const TemplateDictionaryInterface* dictionary,
                    PerExpandData* per_expand_data,
                    std::string* output_buffer) const {
    if (output_buffer == NULL)  return false;
    StringEmitter e(output_buffer);
    return ExpandNoLoad(filename, strip, dictionary, per_expand_data, &e);
  }

  // ---- FINDING A TEMPLATE FILE -------

  // Sets the root directory for all templates used by the program.
  // After calling this method, the filename passed to GetTemplate may
  // be a relative pathname (no leading '/'), in which case this
  // root-directory is prepended to the filename.  This clears the old
  // 'main' root directory, and also all alternate root directories
  // that may had been added previously.
  bool SetTemplateRootDirectory(const std::string& directory);

  // Adds an additional search path for all templates used by the
  // program.  You may call this multiple times.
  bool AddAlternateTemplateRootDirectory(const std::string& directory);

  // Returns the 'main' root directory set by SetTemplateRootDirectory().
  std::string template_root_directory() const;

  // Given an unresolved filename, look through the template search
  // path to see if the template can be found. If so, return the path
  // of the resolved filename, otherwise return an empty string.
  std::string FindTemplateFilename(const std::string& unresolved)
      const;

  // ---- MANAGING THE CACHE -------
  //   Freeze
  //   Delete
  //   ClearCache
  //   ReloadAllIfChanged
  //   Clone

  // Marks the template cache as immutable. After this method is called,
  // the cache can no longer be modified by loading new templates or
  // reloading existing templates. During expansion only cached
  // included templates will be used, they won't be loaded on-demand.
  void Freeze();

  // Delete
  //   Deletes one template object from the cache, if it exists.
  //   This can be used for either file- or string-based templates.
  //   Returns true if the object was deleted, false otherwise.
  bool Delete(const TemplateString& key);

  // ClearCache
  //   Deletes all the template objects in the cache and all raw
  //   contents cached from StringToTemplateCache. This should only
  //   be done once, just before exiting the program and after all
  //   template expansions are completed. (If you want to refresh the
  //   cache, the correct method to use is ReloadAllIfChanged, not
  //   this one.) Note: this method is not necessary unless you are
  //   testing for memory leaks. Calling this before exiting the
  //   program will prevent unnecessary reporting in that case.
  void ClearCache();

  // ReloadAllIfChanged
  //   If IMMEDIATE_RELOAD, reloads and parses all templates right away,
  //   if the corresponding template files have changed.
  //   If LAZY_RELOAD, then sets the reload bit on all templates.
  //   Subsequent call to GetTemplate() checks if file has changed, and if so
  //   reloads and parses the file into the cache.
  //
  //   IMMEDIATE_RELOAD gives a more consistent snapshot of the current
  //   templates, since all templates in the cache are reloaded at
  //   (approximately) the same time.  On the other hand, LAZY_RELOAD
  //   causes less of a latency spike, since it does not require
  //   loading lots of templates from disk at the same time.  If in
  //   doubt, LAZY_RELOAD is probably a better choice.

  //   If a file with the same name as an existing template-file, is added
  //   in another search path, ReloadAllIfChanged will pick up the file in the
  //   earlier search-path.
  enum ReloadType { LAZY_RELOAD, IMMEDIATE_RELOAD };
  void ReloadAllIfChanged(ReloadType reload_tyle);

  // Clone
  //   Returns a copy of the cache. It makes a shallow copy of the
  //   parsed_template_cache_, incrementing refcount of templates.
  //   The caller is responsible for deallocating the returned TemplateCache.
  //   NOTE(user): Annotalysis expects this method to have a lock for
  //                 a TemplateCache instance local to the method, but we
  //                 know that no other threads will have access to the
  //                 instance, so ignore thread safety errors.
  TemplateCache* Clone() const;

  // ---- INSPECTING THE CACHE -------
  //   Dump
  //   DumpToString
  // TODO(csilvers): implement these?

 private:
  // TODO(csilvers): nix Template friend once Template::ReloadIfChanged is gone
  friend class Template;   // for ResolveTemplateFilename
  friend class TemplateTemplateNode;   // for ExpandLocked
  friend class TemplateCachePeer;   // for unittests
  friend class ::TemplateCacheUnittest;  // for unittests

  class RefcountedTemplate;
  struct CachedTemplate;
  class TemplateCacheHash;
  class RefTplPtrHash;
  // due to a bug(?) in MSVC, TemplateCachePeer won't compile unless this
  // particular typedef is public.  Ugh.
 public:
  typedef std::pair<TemplateId, int> TemplateCacheKey;
 private:
  typedef std::map<TemplateCacheKey, CachedTemplate, TemplateCacheHash>
    TemplateMap;
  typedef std::map<RefcountedTemplate*, int, RefTplPtrHash> TemplateCallMap;
  // Where to search for files.
  typedef std::vector<std::string> TemplateSearchPath;

  // GetTemplate
  //   This method is deprecated. It exists here because it is called by
  //   Template::GetTemplate. Also this is used in tests.
  const Template* GetTemplate(const TemplateString& key, Strip strip);

  bool ResolveTemplateFilename(const std::string& unresolved,
                               std::string* resolved,
                               FileStat* statbuf) const;

  // This is used only for internal (recursive) calls to Expand due
  // to internal template-includes.  It doesn't try to acquire the
  // global template_lock again, in template.cc.
  // TODO(csilvers): remove this when template.cc's g_template_lock goes away.
  bool ExpandLocked(const TemplateString& filename, Strip strip,
                    ExpandEmitter* output,
                    const TemplateDictionaryInterface *dictionary,
                    PerExpandData* per_expand_data);

  bool AddAlternateTemplateRootDirectoryHelper(
      const std::string& directory,
      bool clear_template_search_path);

  // DoneWithGetTemplatePtrs
  //   For historical reasons, GetTemplate() returns a raw Template
  //   pointer rather than a refcounted pointer.  So it's impossible
  //   for the user to call DecRef on the template when it's done
  //   using it.  To make up for that, we provide this routine, which
  //   says "call DecRef()" on *all* Templates ever used by
  //   GetTemplate().  It's safe for the client to call this when it's
  //   done using all templates it's ever retrieved before (via
  //   GetTemplate).  Most likely, the user will call this indirectly,
  //   via ClearCache().
  //   TODO(panicker): Consider making this method public.
  void DoneWithGetTemplatePtrs();

  // ValidTemplateFilename
  //   Validates the user provided filename before constructing the template
  bool IsValidTemplateFilename(const std::string& filename,
                               std::string* resolved_filename,
                               FileStat* statbuf) const;

  // GetTemplateLocked
  //   Internal version of GetTemplate. It's used when the function already
  //   has a write-lock on mutex_.  It returns a pointer to a refcounted
  //   template (in the cache), or NULL if the template is not found.
  //   Its used by GetTemplate & ForceReloadAllIfChanged.
  RefcountedTemplate* GetTemplateLocked(
      const TemplateString& filename,
      Strip strip,
      const TemplateCacheKey& key);

  // Refcount
  //  Testing only. Returns the refcount of a template, given its cache key.
  int Refcount(const TemplateCacheKey template_cache_key) const;

  // GetCachedTemplate
  //  Debug only. Returns whether the cache key is in the parsed cache.
  bool TemplateIsCached(const TemplateCacheKey template_cache_key) const;

  TemplateMap* parsed_template_cache_;
  bool is_frozen_;
  TemplateSearchPath search_path_;

  // Since GetTemplate() returns a raw pointer, it's impossible for
  // the caller to call DecRef() on the returned template when it's
  // done using it.  To make up for that, we store each retval of
  // GetTemplate in this data structure.  Then the user can call
  // DecRef() on all of them at once, via a DoneWithGetTemplatePtrs()
  // (which they will probably get at via a call to ClearCache()).
  TemplateCallMap* get_template_calls_;

  Mutex* const mutex_;
  Mutex* const search_path_mutex_;

  // Can't invoke copy constructor or assignment operator
  TemplateCache(const TemplateCache&);
  void operator=(const TemplateCache &);
};

}

#endif  // TEMPLATE_TEMPLATE_CACHE_H_
