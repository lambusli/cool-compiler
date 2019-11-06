class Queen {
    pane : Int;
};

class King inherits Queen {};

class Bishop inherits Queen {
    soldier : Int;
};

class A inherits King {
    kA1 : King;
    bA1 : Bishop;
    xA1 : Int <- (if true then 5 else 3 fi);
    xA2 : Int <- (if true then "cond" else 3 fi);
    xA4 : Int <- (if true then kA1 else bA1 fi);
};

class B inherits Bishop {
    xB1 : Int <- {new SELF_TYPE; new A; };
    xB2 : Int <- {5; if true then soldier else 5 fi; };
    xB3 : Int <- {5; "str";};
};

class Test {
    s : String;
    xL3 : Int <- (let s : SELF_TYPE <- (new LetTest) in s);
    xL4 : Int <- (let s : SELF_TYPE <- (new LetTest) in (if true then s else 5 fi));
};

class LetTest inherits Test {

    xL1 : Int <- (let s : Int <- 5 in true);
    xL2 : Int <- (let s : Int in true);

};
