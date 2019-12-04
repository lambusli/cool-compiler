class A inherits IO {};

class B inherits A {};

class Main inherits IO {
    s_void : IO;
    s_yes : IO <- (new IO);
    main() : Object {{
        --s_void.out_string("hello recv 1\n");
        (new IO).out_string("hello recv 2\n");
        s_yes.out_string("hello recv 3\n");
        (new B).out_string("hello recv B\n");
        --(new SELF_TYPE).out_string("hello recv 4\n");
    }};
};
