function checkFlag(s) {
  const encoded = [49, 102, 111, 51, 119, 52, 56, 99, 74, 64, 78, 45, 245, 138, 73, 6, 190, 98, 41, 38, 50, 177, 31, 174, 82, 32, 82, 42];

  let F = (n) => {
    if (n == 0) {
      return 0;
    } else if (n == 1) {
      return 1;
    } else {
      return F(n - 1) + F(n - 2);
    }
  };

  if (s.length != 36) {
    return false;
  }

  if (s.slice(0, 7) != "RicSec{" || s.slice(-1) != "}") {
    return false;
  }

  for (let i = 0; i < 28; i++) {
    let e = s.charCodeAt(i + 7) ^ (F(i) & 0xff);
    if (e != encoded[i]) {
      return false;
    }
  }

  return true;
}

function main() {
  if (process.argv.length != 3) {
    console.log("Usage: check.sh <flag>");
    process.exit(1);
  }

  const flag = process.argv[2];
  if (checkFlag(flag)) {
    console.log("Correct")
  } else {
    console.log("Wrong")
  }
}

main()
