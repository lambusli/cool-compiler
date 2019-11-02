class A {
	a : Int;
	b : Bool;
	init(x : Int, y : Bool) : A { {
		a <- x;
		b <- y;
		self;
    } };
};

class B inherits A {
    a: Int;
    banana: Bool;
};

class C inherits A {
    ankor: Int;
    b: Bool;
};

class D inherits B {
    angel: Int;
    bail: Bool;
};

Class Main {
	main():A {
	  (new A).init(1, true)
	};
};
