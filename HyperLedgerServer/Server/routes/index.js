var express = require('express');
var Single = require('../SingleTone');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  // res.send(single.ski + 1);
  res.send(`+1`)
});

module.exports = router;
