function as(f, s, t) {
    this.value = f;
    this.item = s;
    this.id = t;
}
var a = new as(15, "apple", 0x96487);
var b = new as(9, "banana", 0xf4d59);
var c = 96;

function change(dd) {
    if (dd.constructor === Object) dd.value = 159;
    else dd = 969;
}

change(c);

if (a.constructor === as) console.log("yes");

console.log(c);
