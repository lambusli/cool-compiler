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
    --xB4 : Int <- (isvoid 5);
};

class Test {
    s : String;
    t : SELF_TYPE;
    t2 : LetTest;
    r1 : Int;
    r2 : String;
    xT0 : Int <- {
        t <- (new SELF_TYPE);
        --t <- (new LetTest);
        --t2 <- (new SELF_TYPE);
    };
    --xT1 : Int <- (let s : SELF_TYPE <- (new LetTest) in s);
    xT2 : Int <- (let s : SELF_TYPE in (if true then s else 5 fi));
    --xT3 : Int <- (let tar : Int, s : SELF_TYPE <- (new LetTest) in (s));
    xT3 : Int <- (let tar : Int, s : Test <- (new SELF_TYPE) in (s));
};

class LetTest inherits Test {
    xL0 : Int <- {
        t2 <- (new SELF_TYPE);
    };
    xL1 : Int <- (let s : Int <- 5 in true);
    xL2 : Int <- (let s : Int in true);
    xL3 : Int <- (let what : Int in s);

};

class CaseTest inherits Test {
    xC1 : Int <- (
        case 0 of r1 : Bishop => r1; r2 : King => r2; esac
    );
    xC2 : Int <- (
        case 0 of rho1 : Int => r1; r2 : Int => r2; esac
    );
};

class Un {
    xU1 : Int <- {
        isvoid (if true then 5 else 10 fi);
        not (true);
        ~ (5);
    };
};

class Bin {
    --xBin1 : Int <- {3 + 4; 3 - 4; 3 * 4; 3 / 4; 3 < 4; 3 <= 4; };
    xBin2 : Int <- {
        true = false;
        1 = 2;
        "ad" = "bc";
        (new Queen) = (new King);
    };
};
