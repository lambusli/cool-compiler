class A inherits IO {
    show() : Object {out_string("I am A\n") };
};

class B inherits C {
    show() : Object {out_string("I am B\n")};
};

class C inherits A {
    show() : Object {out_string("I am C\n")};
};

class D inherits A {
    show() : Object {out_string("I am D\n")};
};

class Main inherits IO {
    obj : A <- new B;
    main() : Object {{
        case obj of
            obj : A => {obj <- new A; obj.show();};
            --obj : B => {obj <- new B; obj.show();};
            obj : C => {obj <- new C; obj.show();};
            obj : D => {obj <- new D; obj.show();};
        esac;
        obj.show();
    }};
};
