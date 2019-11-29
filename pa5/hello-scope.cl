class Main inherits IO {
    x : Int <- 5;
    show_on(x : Int) : Object {out_int(x)};
    show_off() : Object {out_int(x)};
    main() : Object {{
        show_on(7);
        show_off();
    }};
};
