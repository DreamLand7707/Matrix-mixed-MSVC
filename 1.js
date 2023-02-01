function ace() {
    var a = document.getElementById("pop");
    var b;
    var posadd = 0;
    b = setInterval(function () {
        if (posadd <= 450) {
            a.style.top = posadd + "px";
            a.style.left = posadd + "px";
            posadd++;
        } else {
            clearInterval(b);
        }
    }, 5);
}
