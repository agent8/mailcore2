#ifndef MAILCORE_MUTF7STRING_H
#define MAILCORE_MUTF7STRING_H
#include <MailCore/MCBaseTypes.h>
#ifdef __cplusplus
namespace mailcore {
	class MAILCORE_EXPORT Utf7String : public Object{
	public:
		static String * jencodeMutf7(String * src);
		static String * jdecodeMutf7(String * src);
		static String * jflattenHTML(String * src);
		static String * jtransferEncodingDecode(Data * data, int encoding, String * charset, bool isHTML);

		static String * jencodeRFC822Str(String * src);
		static String * jdecodeRFC822Str(String * src);

		static String * jhtmlEncodedString(String * src);
		static void setupCode();
		static void setupICU4C(String * src);
	};
}
#endif
#endif