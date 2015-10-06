all:
	javac JNILab.java
	javah JNILab
	gcc -dynamiclib -o libchartest.jnilib -I/Library/Java/JavaVirtualMachines/jdk1.8.0_60.jdk/Contents/Home/include -I/Library/Java/JavaVirtualMachines/jdk1.8.0_60.jdk/Contents/Home/include/darwin/ chartest.c -framework JavaVM
	export LD_LIBRARY_PATH=$${LD_LIBRARY_PATH}:.

clean:
	rm -f libchartest.jnilib
	rm -f JNILab.class
