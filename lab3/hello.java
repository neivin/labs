import java.io.*;

public class hello {
	static {System.loadLibrary("hello");}

	//declare native method
	native int get_random(int range);

	public static void main(String[] args){
		hello gen = new hello();
		
		for (int i = 10; i < 100 ; i+=10)
			System.out.println("Rand("+i+")="+gen.get_random(i));
	}
}
