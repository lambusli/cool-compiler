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

    fA2(argc : Int) : SELF_TYPE {new SELF_TYPE};
    mainA : Object <- {
        let gen : Pawn <- (new Pawn) in (coup(new Pawn, 5, 10));

    };
};

class B inherits A {
};
