class Main inherits IO {
    x : Int <- 5;
    s : String <- "\nLook here\n";
    show_on(x : Int) : Object {out_int(x)};
    show_off() : Object {out_int(x)};
    show_word(x : String) : Object {out_string(x)};
    main() : Object {{
        show_on(7);
        show_off();
        show_word(s);
    }};
};
