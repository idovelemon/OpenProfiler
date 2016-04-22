/**
* Define the text window which will watch some values at real time.
* @param {string} title The title of the text window
* @param {string} canvas_id The canvas_id of the HTML Canvas tag<canvas id=canvas_id></canvas>
* @type {class}
* @constructor
*/
openprofiler.window.TextWindow = function(title, canvas_id) {
	openprofiler.window.BaseWindow.call(this, title, 0, 0, canvas_id);
};

/**
* @extend {BaseWindow}
*/
openprofiler.window.TextWindow.prototype = new openprofiler.window.BaseWindow();