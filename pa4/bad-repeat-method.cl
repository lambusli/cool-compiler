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
    evolve(animal : Int) : Bool {0};
    uneq(x : Int) : Bool {0};
};

class C inherits A {
    ankor: Int;
    bond: Bool;
    offense(x : Int, y : B) : C {0};
    init(xx : Bool, yy : Int) : A {0};
};

class D inherits B {
    angel: Int;
    bail: Bool;
    defense() : Int {0};
    evolve(panda : Int) : Bool {0};
    uneq(x : Int, y : Int) : Bool {0};
};

Class Main {
	main():A {
	  (new A).init(1, true)
	};
};
