public class JNILab{
	static {System.loadLibrary("chartest"); }

	native int testChar(char ch);

	public static void main(String[] args){
		JNILab gen = new JNILab();
		
		if(gen.testChar('A') == 1){
			System.out.println("true");
		}
		else {
			System.out.println("false");
		}
	}
}
