#include <jni.h>

JNIEXPORT jint JNICALL Java_JNILab_testChar
	(JNIEnv * env, jobject obj, jchar ch) {
	
	int c = (int) ch;

	if(c>='A' && c<='Z')
		return 1;
	else if(c>='a' && c<='z')
		return 0;
	return 0;
}
