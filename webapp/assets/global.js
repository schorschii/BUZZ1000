// sound definitions
var sounds = {
	"barbiegirl":"Barbie Girl",
	"buzzer":"Classic Buzzer",
	"fanfare":"Fanfare",
	"fart":"Fart",
	"gun1":"Gun 1",
	"gun2":"Gun 2",
	"gun3":"Gun 3",
	"quack":"Quack",
	"servicebell":"Service Bell",
	"slotmachine":"Slotmachine",
	"tvtotal":"TV-Total-Buzzer",
	"gong":"Gong",
	"cork":"Cork",
	"schweinebacke":"Yippie-Ya-Yay Schweinebacke",
	"egal":"Egal",
	"angry-scream":"Angry Scream",
	"confused-scream":"Confused Scream",
	"wilhelm-scream":"Wilhelm Scream",
	"beethoven":"Beethoven",
	"bhc":"Beverly Hills Cop",
	"cat":"Cat",
	"crazy-chick":"Crazy Chick",
	"duck":"Duck",
	"froehlich":"Warum bin ich so fröhlich",
	"groan":"Groan",
	"otto":"Otto",
	"whip":"Whip",
	"ringelingeling":"Ringelingeling",
	"sendung-mit-der-maus":"Sendung mit der Maus",
	"shaver":"Shaver",
	"travelling-with-deutsche-bahn":"Thank you for travelling with DB",
	"tusch":"Tusch",
	"haha":"Ha Ha"
};

function prefetchSounds() {
	for(index in sounds) {
		document.head.innerHTML += '<link rel="prefetch" href="sounds/'+index+'.mp3" as="audio">';
	}
}

// cookie functions
function setCookie(name,value,days) {
	var expires = "";
	if (days) {
		var date = new Date();
		date.setTime(date.getTime() + (days*24*60*60*1000));
		expires = "; expires=" + date.toUTCString();
	}
	document.cookie = name + "=" + (value || "")  + expires + "; path=/";
}
function getCookie(name) {
	var nameEQ = name + "=";
	var ca = document.cookie.split(';');
	for(var i=0;i < ca.length;i++) {
		var c = ca[i];
		while (c.charAt(0)==' ') c = c.substring(1,c.length);
		if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
	}
	return null;
}
function eraseCookie(name) {
	document.cookie = name +'=; Path=/; Expires=Thu, 01 Jan 1970 00:00:01 GMT;';
}
