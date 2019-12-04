class Main inherits IO {
    main() : Object {{
        (new SELF_TYPE).out_string("hello self type\n");
        --(new IO).out_string("This is new IO\n");
    }};
};
