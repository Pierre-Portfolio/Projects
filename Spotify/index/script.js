var vid = document.getElementById("bgvid");
var pauseButton = document.querySelector("#logo button");

pauseButton.addEventListener("click", function() {
  vid.classList.toggle("stopfade");
  if (vid.paused) {
    vid.play();
  } else {
    vid.pause();
  }
})

