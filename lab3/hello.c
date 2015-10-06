#include <jni.h>
#include <stdlib.h>
#include "hello.h"

JNIEXPORT jint JNICALL Java_hello_get_1random
  (JNIEnv *env, jobject obj, jint seed)
{
	return(rand() % seed);
}
