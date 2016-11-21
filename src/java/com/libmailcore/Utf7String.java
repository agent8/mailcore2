package com.libmailcore;
public class Utf7String extends NativeObject {
	public native static String encodeMutf7(String src);
	public native static String decodeMutf7(String src);
	public native static String flattenHTML(String src);
	public native static String transferEncodingDecode(byte[] data, int encoding, String charset, boolean isHTML);

	public native static String encodeRFC822Str(String src);
	public native static String decodeRFC822Str(String src);

	public native static String htmlEncodedString(String src);

	public native static void setupCode();
	private native void setupNative();

    private static final long serialVersionUID = 1L;
    public Utf7String()
    {
        setupNative();
    }
}