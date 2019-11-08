class Queen {
    pane : Int;
};

class King inherits Queen {};

class Bishop inherits Queen {
    soldier : Int;
    coup(p1 : Pawn, date : Int) : SELF_TYPE {self};
};

class Pawn {};

class A inherits Bishop {
    coup(p1 : Pawn, date : Int) : SELF_TYPE {self};
    fA2(argc : Int) : SELF_TYPE {new SELF_TYPE};
    mainA : Object <- {
        --let gen : Pawn <- (new Pawn) in (coup(new Pawn, 5, 10));
        --let gen : Pawn <- (new Pawn) in (coup(new Pawn, true));
        let gen : Pawn <- (new Pawn) in (coup(new Pawn, 5));
        self@Bishop.coup(new Pawn, 5);
    };
};

class B inherits A {
};

class Main inherits IO {
    temp : B;
    fM1(x : Int, y : Int) : Int {0};
    main() : SELF_TYPE {{
        if (true = true.copy()) then
            out_string("c")
        else
            out_string("w")
        fi;
        self;
    }};

};
