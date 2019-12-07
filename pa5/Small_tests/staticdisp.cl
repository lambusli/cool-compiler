class A inherits IO {
    show() : Object {out_string("I am A\n")};
};

class B inherits A {
    show() : Object {out_string("I am B\n")};
};

class Main inherits IO {
    obj : B <- new B;
    main() : Object {{
        obj@A.show();
        obj.show(); 
    }};
};
