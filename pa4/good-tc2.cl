class Queen {
    pane : Int;
};

class King inherits Queen {};

class Bishop inherits Queen {
    soldier : Int;
};

class AAA inherits King {
    kA1 : King;
    bA1 : Bishop;
    xA1 : Object <- (if true then 5 else 3 fi);
    xA2 : Object <- (if true then "cond" else 3 fi);
    xA4 : Object <- (if true then kA1 else bA1 fi);
};

class BBB inherits Bishop {
    xB1 : Object <- {new SELF_TYPE; new AAA; };
    xB2 : Object <- {5; if true then soldier else 5 fi; };
    xB3 : Object <- {5; "str";};
    --xB4 : Object <- (isvoid 5);
};

class Test {
    s : String;
    t : SELF_TYPE;
    t2 : LetTest;
    r1 : Int;
    r2 : String;
    xT0 : Object <- {
        t <- (new SELF_TYPE);
        --t <- (new LetTest);
        --t2 <- (new SELF_TYPE);
    };
    --xT1 : Object <- (let s : SELF_TYPE <- (new LetTest) in s);
    xT2 : Object <- (let s : SELF_TYPE in (if true then s else 5 fi));
    --xT3 : Object <- (let tar : Int, s : SELF_TYPE <- (new LetTest) in (s));
    xT3 : Object <- (let tar : Int, s : Test <- (new SELF_TYPE) in (s));
};

class LetTest inherits Test {
    xL0 : Object <- {
        t2 <- (new SELF_TYPE);
    };
    xL1 : Object <- (let s : Int <- 5 in true);
    xL2 : Object <- (let s : Int in true);
    xL3 : Object <- (let what : Int in s);

};

class CaseTest inherits Test {
    xC1 : Object <- (
        case 0 of r1 : Bishop => r1; r2 : King => r2; esac
    );
    xC2 : Object <- (
        case 0 of rho1 : Int => r1; r2 : Int => r2; esac
    );
};

class Un {
    xU1 : Object <- {
        isvoid (if true then 5 else 10 fi);
        not (true);
        ~ (5);
    };
};

class Bin {
    --xBin1 : Object <- {3 + 4; 3 - 4; 3 * 4; 3 / 4; 3 < 4; 3 <= 4; };
    xBin2 : Object <- {
        true = false;
        1 = 2;
        "ad" = "bc";
        (new Queen) = (new King);
    };
};
