// Copyright (c) 2006, Google Inc.
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
// This class implements some template helper classes, that manage
// template files and make it easier to monitor them.
//
// For information about how to use these classes and macros, and to
// write the templates it takes as input,
// see the doc/ directory.

#ifndef TEMPLATE_TEMPLATE_NAMELIST_H_
#define TEMPLATE_TEMPLATE_NAMELIST_H_

#include <time.h>    // for time_t
#include <set>
#include <string>
#include <vector>
#include <ctemplate/template_enums.h>    // for Strip
#include <ctemplate/template_string.h>   // for StringHash



namespace ctemplate {

// RegisterTemplateFilename
//   Used to define a reference variable for the name of a template file. E.g:
//        RegisterTemplateFilename(EXAMPLE_FN, "example.tpl");
//   This should be used rather than the seemingly equivalent:
//        #define EXAMPLE_FN "example.tpl"
//   As in the latter, any call to GetTemplate may then reference the name
//   via the first argument. In the example, that would be:
//        Template::GetTemplate(EXAMPLE_FN, DO_NOT_STRIP);
//   By using this macro, rather than the #define, all templates can
//   later be tested for either existence or correct syntax after program
//   start-up.
// TODO (we wish): Make this macro produce the #include for the auto-generated
// header files, when and if the macro pre-processor supports that
#define RegisterTemplateFilename(var, name)         \
  const char* const var = ::ctemplate::TemplateNamelist::RegisterTemplate(name);

// Class: TemplateNamelist
//   Each time this class is instantiated, the name passed to
//   the constructor is added to the class's static list of names. The
//   entire list may be retrieved later by calling the GetList accessor
//   method. Or they may all be checked for existence or for correct
//   syntax via the other methods. We use this in our
//   sanity-checking code to make sure all the templates used by a program
//   exist and are syntactically correct.

class  TemplateNamelist {
  friend class TemporaryRegisterTemplate;
 public:
  // These types should be taken as 'generic' containers.  The only
  // thing you should do with them is call size() and/or iterate
  // between begin() and end(), and the only operations we promise
  // the iterators will support are operator* and operator++.
  typedef std::set<std::string, StringHash> NameListType;
  typedef std::vector<std::string> MissingListType;
  typedef std::vector<std::string> SyntaxListType;

 public:
  // Takes a name and pushes it onto the static namelist
  // Returns: a pointer to the entry in namelist which holds the name
  static const char* RegisterTemplate(const char* name);

  // GetList
  // Description: Returns the collected list of names.
  static const NameListType& GetList();

  // GetMissingList
  //   If refresh is true or if it is the first time the function is called
  //   in the execution of the program, it creates (or clears) the missing
  //   list and then fills it with the list of
  //   templates that the program knows about but are missing from
  //   the template directory.
  //   If refresh is false and it is not the first time the function is
  //   called, it merely returns the list created in the
  //   call when the last refresh was done.
  //   NOTE: The templates are NOT read, parsed, or cached
  //   by this function.
  static const MissingListType& GetMissingList(bool refresh);

  // GetBadSyntaxList
  //   If refresh is true or if it is the first time the function is called
  //   in the execution of the program, it creates (or clears) the "bad
  //   syntax" list and then fills it with the list of
  //   templates that the program knows about but contain syntax errors.
  //   A missing file is not considered a syntax error, and thus is
  //   not included in this list.
  //   If refresh is false and it is not the first time the function is
  //   called, it merely returns the list created in the
  //   call when the last refresh was done.
  //   NOTE: The side effect of calling this the first time or
  //   with refresh equal true is that all templates are parsed and cached.
  //   Hence they need to be retrieved with the flags that
  //   the program needs them loaded with (i.e, the strip parameter
  //   passed to Template::GetTemplate.)
  static const SyntaxListType& GetBadSyntaxList(bool refresh, Strip strip);

  // GetLastmodTime
  //   Iterates through all non-missing templates, and returns the latest
  //   last-modification time for the template files, as returned by stat().
  //   This can be used to make sure template files are getting refreshed.
  static time_t GetLastmodTime();

  // AllDoExist
  //   Retrieves the missing list (always refreshing the list)
  //   and returns true if it contains any names.
  //   Else, returns false.
  static bool AllDoExist();

  // IsAllSyntaxOkay
  //   Retrieves the "bad syntax" list (always refreshing the list)
  //   and returns true if it contains any names.
  //   Else, returns false.
  //   NOTE: The side effect of calling this is that all templates are parsed
  //   and cached, hence they need to be retrieved with the flags that
  //   the program needs them loaded with. (I.e, the strip parameter
  //   ultimately passed to Template::GetTemplate.)
  static bool IsAllSyntaxOkay(Strip strip);

 protected:
  // The static list of names
  static NameListType *namelist_;
  static MissingListType *missing_list_;
  static SyntaxListType *bad_syntax_list_;

 private:
  TemplateNamelist(const TemplateNamelist&);   // disallow copying
  void operator=(const TemplateNamelist&);
};

}


#endif  // TEMPLATE_TEMPLATE_NAMELIST_H_
