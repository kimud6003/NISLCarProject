#!/bin/bash
set -ev

# install chaincode for channelsales1
docker exec cli peer chaincode install -n smartcar-cc -v 1.0 -p chaincode/go
sleep 1
# instantiate chaincode for channelsales1
docker exec cli peer chaincode instantiate -o orderer.smartcar.com:7050 -C channelsales1 -n smartcar-cc -v 1.0 -c '{"Args":[""]}' -P "OR ('Sales1Org.member','Sales2Org.member')"
sleep 2
# # invoke chaincode for channelsales2
docker exec cli peer chaincode invoke -o orderer.smartcar.com:7050 -C channelsales1 -n smartcar-cc -c '{"function":"setWallet","Args":["Q", "B","C" ,"D", "E","F"]}'
sleep 1
# # query chaincode for channelsales1
docker exec cli peer chaincode query -o orderer.smartcar.com:7050 -C channelsales1 -n smartcar-cc -c '{"function":"getAllWallet","Args":[""]}'
sleep 1

docker exec cli peer chaincode invoke -o orderer.smartcar.com:7050 -C channelsales1 -n smartcar-cc -c '{"function":"setRentRecord","Args":["a","b"]}'
sleep 1

docker exec cli peer chaincode query -o orderer.smartcar.com:7050 -C channelsales1 -n smartcar-cc -c '{"function":"getRentRecord","Args":["b3aa0ff0c26f4eb8c4f7f44014dd862b0b6c660717653bd8ae22486b1e4823d5"]}'
# sleep 1
