class Main inherits IO {
    double(x : Int) : Int {2 * x};
    y : Int <- (let z : Int <- 5 in double(z));
    main() : Object {{
        out_int(y);
    }};
};
