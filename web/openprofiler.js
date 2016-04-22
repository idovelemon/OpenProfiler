/**
 * Define a single gloable namespace. This namespace will hold all the class and method.
 * @type {namespace}
 */
var openprofiler = {};

/**
 * Define a namespace in openprofiler.
 * All kinds of windows will be hold in this namespace.
 * @type {namespace}
 */
openprofiler.window = {};

/**
 * Define the base window class. All the windows in openprofiler will inherit from this.
 * All profile windows are implemented base on the HTML5 Canvas.
 * @type {class}
 * @constructor
 */
openprofiler.window.BaseWindow = function(title, width, height, canvas_id) {
	this.title = title;
	this.width = width;
	this.height = height;
	this.x = 0;
	this.y = 0;
	this.draggable = true;
	this.canvas = null;
	this.canvas_id = canvas_id;

	/**
	 * Create the canvas which the window will draw on.
	 * @param  {string} canvas_id The id segment in <canvas id=canvas_id></canvas>
	 * @param  {number} canvas_width The canvas_width segment in <canvas width=canvas_width></canvas>
	 * @param  {number} canvas_height The canvas_height segment in <canvas height=canvas_height></canvas>
	 * @param  {boolean} draggable The draggable segment in <canvas draggable=true|false></canvas>
	 * @return {canvas}           [description]
	 */
	var createCanvas_ = function(canvas_id, canvas_width, canvas_height, draggable) {
		// Build the canvas tag.
		var tag = '<canvas' +
			' id=' + '"' + canvas_id + '"'
			+ ' width=' + canvas_width
			+ ' height=' + canvas_height
			+ ' draggable=' + draggable
			+ '>'
			+ 'This browser does not support Canvas!'
			+ '</canvas>';

		// Write the html tag
		document.write(tag);

		// Get the canvas element
		canvas = document.getElementById(canvas_id);

		if (canvas == null) {
			alert(tag + ' is invalid html tag');
		}

		return canvas;
	};

	this.canvas = createCanvas_(this.canvas_id, this.width, this.height, this.draggable);
	this.canvas.style.position = 'absolute';
	this.canvas.style.left = '0px';
	this.canvas.style.top = '0px';

	var cur_wnd_ = this;
	this.canvas.getOwnerWindow = function() {
		return cur_wnd_;
	};

	var click_pos_ = {
		x: 0,
		y: 0,
	};

	this.canvas.ondragstart = function(event) {
		click_pos_.x = event.clientX;
		click_pos_.y = event.clientY;
	};

	this.canvas.ondrag = function(event) {
		if (this.getOwnerWindow().isDraggable()) {
			if (event.clientX == 0
				&& event.clientY == 0) {
				return;
			};

			var cur_pos_ = {
				x: event.clientX,
				y: event.clientY,
			};

			var diff_ = {
				x: cur_pos_.x - click_pos_.x,
				y: cur_pos_.y - click_pos_.y,
			};

			var window_x_ = this.getOwnerWindow().getX();
			var window_y_ = this.getOwnerWindow().getY();
			window_x_ = window_x_ + diff_.x;
			window_y_ = window_y_ + diff_.y;
			this.getOwnerWindow().setX(window_x_);
			this.getOwnerWindow().setY(window_y_);

			click_pos_ = cur_pos_;

			this.style.position = 'absolute';
			this.style.left = window_x_ + 'px';
			this.style.top = window_y_ + 'px';
		}
	};

	this.canvas.ondragend = function(event) {
		if (this.getOwnerWindow().isDraggable()) {
			var cur_pos_ = {
				x: event.clientX,
				y: event.clientY,
			};

			var diff_ = {
				x: cur_pos_.x - click_pos_.x,
				y: cur_pos_.y - click_pos_.y,
			};

			var window_x_ = this.getOwnerWindow().getX();
			var window_y_ = this.getOwnerWindow().getY();
			window_x_ = window_x_ + diff_.x;
			window_y_ = window_y_ + diff_.y;
			this.getOwnerWindow().setX(window_x_);
			this.getOwnerWindow().setY(window_y_);

			click_pos_ = cur_pos_;

			this.style.position = 'absolute';
			this.style.left = window_x_ + 'px';
			this.style.top = window_y_ + 'px';
		};
	};
};

/**
 * Return the title of the window.
 * @return {string}
 */
openprofiler.window.BaseWindow.prototype.getTitle = function() {
	return this.title;
};

/**
 * Change the window's title.
 * @param {string} new_title
 */
openprofiler.window.BaseWindow.prototype.setTitle = function(new_title) {
	this.title = new_title;
};

/**
 * Return the width of the window.
 * @return {number}
 */
openprofiler.window.BaseWindow.prototype.getWidth = function() {
	return this.width;
};

/**
 * Change the width of the window.
 * @param {number} new_width
 */
openprofiler.window.BaseWindow.prototype.setWidth = function(new_width) {
	this.width = new_width;
};

/**
 * Return the height of the window.
 * @return {number}
 */
openprofiler.window.BaseWindow.prototype.getHeight = function() {
	return this.height;
};

/**
 * Change the height of the window.
 * @param {number} new_height
 */
openprofiler.window.BaseWindow.prototype.setHeight = function(new_height) {
	this.height = new_height;
};

/**
 * Return the left-up corner's x position.
 * @return {number}
 */
openprofiler.window.BaseWindow.prototype.getX = function() {
	return this.x;
};

/**
 * Change the left-up corner's x position.
 * @param {number} new_x
 */
openprofiler.window.BaseWindow.prototype.setX = function(new_x) {
	this.x = new_x;
};

/**
 * Return the left-up corner's y position.
 * @return {number}
 */
openprofiler.window.BaseWindow.prototype.getY = function() {
	return this.y;
};

/**
 * Change the left-up corner's y position.
 * @param {number} new_y
 */
openprofiler.window.BaseWindow.prototype.setY = function(new_y) {
	this.y = new_y;
};

/**
 * Check if the window can be dragged.
 * @return {boolean}
 */
openprofiler.window.BaseWindow.prototype.isDraggable = function() {
	return this.draggable;
};

/**
 * Change the draggable charactics of the window.
 * @param {Boolean} is_draggable true means can drag.
 */
openprofiler.window.BaseWindow.prototype.setDraggable = function(is_draggable) {
	this.draggable = is_draggable;
};

/**
 * Return the canvas the window draw on.
 * @return {canvas}
 */
openprofiler.window.BaseWindow.prototype.getCanvas = function() {
	return this.canvas;
};

/**
 * Draw the windows immediatly.
 */
openprofiler.window.BaseWindow.prototype.draw = function() {
	if (this.canvas == null) {
		return;
	};

	var ctx_ = this.canvas.getContext('2d');
	if (ctx_ == null) {
		return;
	};

	ctx_.clearRect(0, 0, this.width, this.height);
	ctx_.fillStyle = 'rgb(255,0,0)';
	ctx_.fillRect(0, 0, this.width, this.height);
};