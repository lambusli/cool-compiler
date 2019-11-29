class Main inherits IO {
    s : IO;
    main() : Object {{
        s.out_string("hello recv\n");
        (new IO).out_string("hello recv\n"); 
    }};
};
