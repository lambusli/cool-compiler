class C {
	a : Int;
	b : Bool;
	init(x : Int, y : Bool) : C { {
		a <- x;
		b <- y;
		self;
    } };
};

class B inherits C {};

class A inherits C {};

class D inherits A {}; 

Class Main {
	main():C {
	  (new C).init(1, true)
	};
};
