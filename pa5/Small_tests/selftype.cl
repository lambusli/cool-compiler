class Main inherits IO {
    main() : Object {{
        (new SELF_TYPE).out_int(5);
        (new SELF_TYPE).out_string("\nhello self type\n");

        --(new IO).out_string("This is new IO\n");
    }};
};
