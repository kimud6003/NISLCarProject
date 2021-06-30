var express = require('express');
var router = express.Router();
var sdk = require('./sdk');

/* GET users listing. */
router.get('/', function(req, res, next) {
  res.send('respond with a resource');
});

router.get('/getWallet', function (req, res) {
    var walletid = req.query.walletid;
    let args = [walletid];
    sdk.send(false, 'getWallet', args, res);
});
router.get('/setCar', function (req, res) {
    var title = req.query.title;
    var singer = req.query.singer;
    var price = req.query.price;
    var walletid = req.query.walletid;

    let args = [title, singer, price, walletid];
    sdk.send(true, 'setCar', args, res);
});
router.get('/getAllCar', function (req, res) {
    let args = [];
    sdk.send(false, 'getAllCar', args, res);
});
router.get('/purchaseCar', function (req, res) {
    var walletid = req.query.walletid;
    var key = req.query.Carkey;
    
    let args = [walletid, key];
    sdk.send(true, 'purchaseCar', args, res);
});

module.exports = router;
