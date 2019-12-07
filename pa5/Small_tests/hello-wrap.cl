class Main inherits IO {
    printme(s : String, x : Int, y : Int) : Object {{
        out_int(x);
        out_string(s);
        out_int(y);
        out_string("\n"); 
    }};
    main() : Object {printme("\nI am a wrapper\n", 4, 7)};
};
