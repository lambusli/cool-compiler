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
    animal: Int;
    banana: Bool;
    defense(x : Int, y : D) : B {0};
};

class C inherits A {
    ankor: Int;
    bond: Bool;
    offense(x : Int, y : B) : C {0};
};

class D inherits B {
    angel: Int;
    bail: Bool;
    defense(me : Int, enemy : D) : B {0}; 
};

Class Main {
	main():A {
	  (new A).init(1, true)
	};
};
