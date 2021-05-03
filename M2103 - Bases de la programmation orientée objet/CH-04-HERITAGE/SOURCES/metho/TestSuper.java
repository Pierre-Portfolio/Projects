package metho;

public class TestSuper {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}

class A {
	void f () {};
}
class B extends A {
	void f () {};	
}
class C extends B {
	void f () {
		((A) this).f();
	};
}