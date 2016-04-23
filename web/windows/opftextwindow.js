/**
* Define the text window which will watch some values at real time.
* @param {string} title The title of the text window
* @param {string} canvas_id The canvas_id of the HTML Canvas tag<canvas id=canvas_id></canvas>
* @type {class}
* @constructor
*/
openprofiler.window.TextWindow = function(title, canvas_id) {
	openprofiler.window.BaseWindow.call(this, title, 0, 0, canvas_id);
	this.textmap = [];
	this.num_items = 0;
};

/**
* @extend {BaseWindow}
*/
openprofiler.window.TextWindow.prototype = new openprofiler.window.BaseWindow();

/**
* The item window's default height
* @const
*/
openprofiler.window.TextWindow.ITEM_WINDOW_HEIGHT = 32;

/**
* The item's default width
* @const
*/
openprofiler.window.TextWindow.ITEM_WINDOW_WIDTH = 100;

/**
* The title window's height
* @const
*/
openprofiler.window.TextWindow.TITLE_WINDOW_HEIGHT = 20;

/**
* The title window's width
* @const
*/
openprofiler.window.TextWindow.TITLE_WINDOW_WIDTH = 100;

/**
* Insert a text item in the window.
* @param {string} key
* @param {object} value
*/
openprofiler.window.TextWindow.prototype.insertItem = function(key, value) {
	if (key == null) {
		return;
	};

	this.textmap.push({key:key, value:value});
	this.num_items = this.num_items + 1;

	if (this.canvas != null) {
		this.height = this.height + openprofiler.window.TextWindow.ITEM_WINDOW_HEIGHT;
		this.canvas.width = this.width;
		this.canvas.height = this.height;
	};
};

openprofiler.window.TextWindow.prototype.updateItem = function(key, new_value) {
	if (key == null) {
		return;
	};

	for (var cur_num_item = 0; cur_num_item < this.textmap.length; cur_num_item++) {
		if (key == this.textmap[cur_num_item].key) {
			this.textmap[cur_num_item].value = new_value;
			break;
		}
	};
};

openprofiler.window.TextWindow.prototype.init = function() {
	// Call base window's init method
	try {
		openprofiler.window.BaseWindow.prototype.init.call(this);
	} catch(error) {
		// Do noting
	} finally {
		// Do nothing
	}

	this.width = openprofiler.window.TextWindow.TITLE_WINDOW_WIDTH;
	this.height = openprofiler.window.TextWindow.TITLE_WINDOW_HEIGHT;
};

/**
* Draw the text window.
*/
openprofiler.window.TextWindow.prototype.draw = function() {
	if (this.canvas == null) {
		throw Error('Must implement init method in child class. And call init method before child init method');
		return;
	};

	var TextWindow = openprofiler.window.TextWindow;

	var ctx_ = this.canvas.getContext('2d');
	if (ctx_ == null) {
		return;
	};

	ctx_.clearRect(0, 0, this.width, this.height);

	// Draw title
	ctx_.fillStyle = '#00ff00';
	ctx_.fillRect(0, 0, TextWindow.TITLE_WINDOW_WIDTH, TextWindow.TITLE_WINDOW_HEIGHT);
	ctx_.textAlign = 'center';
	ctx_.textBaseline = 'middle';
	ctx_.strokeText(this.title, TextWindow.TITLE_WINDOW_WIDTH / 2, TextWindow.TITLE_WINDOW_HEIGHT / 2);

	// Draw the background
	var cur_num_items = 0;
	while (true) {
		if (cur_num_items >= this.num_items) {
			break;
		};
		
		if (cur_num_items % 2 == 0) {
			ctx_.fillStyle = '#ffff00';
		} else {
			ctx_.fillStyle = '#ff00ff';
		};

		ctx_.fillRect(0, TextWindow.TITLE_WINDOW_HEIGHT + cur_num_items * TextWindow.ITEM_WINDOW_HEIGHT, this.width, TextWindow.ITEM_WINDOW_HEIGHT);
		cur_num_items = cur_num_items + 1;
	};

	// Draw text
	ctx_.textAlign = 'left';
	ctx_.textBaseline = 'middle';
	cur_num_items = 0;
	while (true) {
		if (cur_num_items >= this.num_items) {
			break;
		};

		var x_ = 0;
		var y_ = TextWindow.TITLE_WINDOW_HEIGHT + TextWindow.ITEM_WINDOW_HEIGHT * cur_num_items + TextWindow.ITEM_WINDOW_HEIGHT / 2;
		var item_ = this.textmap[cur_num_items];
		var text_ = item_.key + ':' + item_.value.toString();
		ctx_.strokeText(text_, x_, y_);

		cur_num_items = cur_num_items + 1;
	};

};