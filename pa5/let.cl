class Main inherits IO {
    s : String <- "I am arg\n";
    main() : Object {{
        let s : String <- "I am let init\n" in out_string(s);
        out_string(s); 
    }};
};
