const char MAIN_page[] PROGMEM = R"=====(
<html>
<head>
</head>
<body>
<p> LED Status: <span id="led-state">__</span> </p>
<button onclick="allOn()"> All On </button>
<button onclick="allOff()"> All Off </button>
<button onclick="setHeart()"> Set Heart </button>
<button onclick="setSnake()"> Set Snake </button>
</body>
<script>
function allOn()
{
  console.log("button was clicked!");
  var xhr = new XMLHttpRequest();
  var url = "/allOn";
  xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("led-state").style.background = this.responseText;
    }
  };
  xhr.open("GET", url, true);
  xhr.send();
};
function allOff()
{
  console.log("button was clicked!");
  var xhr = new XMLHttpRequest();
  var url = "/allOff";
  xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("led-state").style.background = this.responseText;
    }
  };
  xhr.open("GET", url, true);
  xhr.send();
};
function setHeart()
{
  console.log("button was clicked!");
  var xhr = new XMLHttpRequest();
  var url = "/setHeart";
  xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("led-state").style.background = this.responseText;
    }
  };
  xhr.open("GET", url, true);
  xhr.send();
};
function setSnake()
{
  console.log("button was clicked!");
  var xhr = new XMLHttpRequest();
  var url = "/setSnake";
  xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("led-state").style.background = this.responseText;
    }
  };
  xhr.open("GET", url, true);
  xhr.send();
};
document.addEventListener('DOMContentLoaded', allOn, false);
document.addEventListener('DOMContentLoaded', allOff, false);
</script>
</html>
)=====";
