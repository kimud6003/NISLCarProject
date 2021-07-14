package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"strconv"
	"github.com/hyperledger/fabric/core/chaincode/shim"
	pb "github.com/hyperledger/fabric/protos/peer"
)

type SmartContract struct{}

type Wallet struct {
	ID       string `json:"ID"`
	PID      string `json:"PID"`
	PK       string `json:"PK"`
	INFO     string `json:"INFO"`
	LOCATION string `json:"LOCATION"`
	STATUS   string `json:"STATUS"`
}

type RentRecord  struct {
	TID    string `json:"TID"`
	CID	   string `json:"CID"`
	H1CODE string `json:"H1CODE"`
}

type WalletKey struct {
	Key string
	Idx int
}

func (s *SmartContract) Init(APIstub shim.ChaincodeStubInterface) pb.Response {
	return shim.Success(nil)
}

func (s *SmartContract) Invoke(APIstub shim.ChaincodeStubInterface) pb.Response {
	function, args := APIstub.GetFunctionAndParameters()

	if function == "setWallet" {
		return s.setWallet(APIstub, args)
	} else if function == "getAllWallet" {
		return s.getAllWallet(APIstub)
	} else if function == "setRentRecord"{
		return s.setRentRecord(APIstub,args)
	} else if function == "getRentRecord"{
		return s.getRentRecord(APIstub,args)
	}
	fmt.Println("Please check your function : " + function)
	return shim.Error("Unknown function")
}

func generateKey(APIstub shim.ChaincodeStubInterface, key string) []byte {
	var isFirst bool = false
	var tempIdx string

	WalletkeyAsBytes, err := APIstub.GetState(key)
	if err != nil {
		fmt.Println(err.Error())
	}

	Walletkey := WalletKey{}
	json.Unmarshal(WalletkeyAsBytes, &Walletkey)
	tempIdx = strconv.Itoa(Walletkey.Idx)
	fmt.Println(Walletkey)
	fmt.Println("Key is " + strconv.Itoa(len(Walletkey.Key)))
	if len(Walletkey.Key) == 0 || Walletkey.Key == "" {
		isFirst = true
		Walletkey.Key = "User"
	}
	if !isFirst {
		Walletkey.Idx = Walletkey.Idx + 1
	}

	fmt.Println("Last WalletKey is " + Walletkey.Key + " : " + tempIdx)
	returnValueBytes, _ := json.Marshal(Walletkey)
	return returnValueBytes
}

func (s *SmartContract) setWallet(APIstub shim.ChaincodeStubInterface, args []string) pb.Response {
	if len(args) != 6 {
		return shim.Error("Incorrect number of arguments. Expecting 2")
	}

	var Walletkey = WalletKey{}
	json.Unmarshal(generateKey(APIstub, "latestKey"), &Walletkey)
	keyidx := strconv.Itoa(Walletkey.Idx)
	fmt.Println("Key : " + Walletkey.Key + ", Idx : " + keyidx)

	var keyString = Walletkey.Key + keyidx
	fmt.Println("Walletkey is " + keyString)

	wallet := Wallet{ID:args[0],PID: args[1],PK:args[2],INFO:args[3],LOCATION:args[4], STATUS: args[5]}
	WalletasJSONBytes, _ := json.Marshal(wallet)

	err := APIstub.PutState(keyString, WalletasJSONBytes)
	if err != nil {
		return shim.Error( fmt.Sprintf("Failed to create Wallet: %s ", Walletkey))
	}

	WalletkeyAsBytes, _ := json.Marshal(Walletkey)
	APIstub.PutState("latestKey", WalletkeyAsBytes)
	
	return shim.Success(nil)
}

func (s *SmartContract) getAllWallet(APIstub shim.ChaincodeStubInterface) pb.Response {
	
	// Find latestKey
	WalletkeyAsBytes, _ := APIstub.GetState("latestKey")
	Walletkey := WalletKey{}
	json.Unmarshal(WalletkeyAsBytes, &Walletkey)
	idxStr := strconv.Itoa(Walletkey.Idx + 1)

	var startKey = "User0"
	var endKey = Walletkey.Key + idxStr
	fmt.Println(startKey)
	fmt.Println(endKey)

	resultsIter, err := APIstub.GetStateByRange(startKey, endKey)
	if err != nil {
		return shim.Error(err.Error())
	}
	defer resultsIter.Close()
	
	var buffer bytes.Buffer
	buffer.WriteString("[")
	bArrayMemberAlreadyWritten := false
	for resultsIter.HasNext() {
		queryResponse, err := resultsIter.Next()
		if err != nil {
			return shim.Error(err.Error())
		}
		
		if bArrayMemberAlreadyWritten == true {
			buffer.WriteString(",")
		}
		buffer.WriteString("{\"Key\":")
		buffer.WriteString("\"")
		buffer.WriteString(queryResponse.Key)
		buffer.WriteString("\"")
		
		buffer.WriteString(", \"Record\":")
		
		buffer.WriteString(string(queryResponse.Value))
		buffer.WriteString("}")
		bArrayMemberAlreadyWritten = true
	}
	buffer.WriteString("]\n")
	return shim.Success(buffer.Bytes())
}

func (s *SmartContract) setRentRecord(APIstub shim.ChaincodeStubInterface, args []string) pb.Response {
	if len(args) != 2 {
		return shim.Error("Incorrect number of arguments. Expecting 2")
	}

	Record:= RentRecord{TID: APIstub.GetTxID(), CID: args[0], H1CODE : args[1]}
	RecordasJSONBytes, _ := json.Marshal(Record)
	result := []byte(RecordasJSONBytes);	
	
	err := APIstub.PutState(Record.TID, RecordasJSONBytes)
	if err != nil {
		return shim.Error("Failed to create RentRecord " + APIstub.GetTxID())
	}

	return shim.Success(result)
}


func (s *SmartContract) getRentRecord(APIstub shim.ChaincodeStubInterface, args []string) pb.Response {

	RentRecordAsBytes, err := APIstub.GetState(args[0])
	if err != nil {
		fmt.Println(err.Error())
	}
	
	rentRecord := RentRecord{}
	json.Unmarshal(RentRecordAsBytes, &rentRecord)
	stringRecord, err := json.Marshal(rentRecord)
    if err != nil {
        fmt.Println(err)
    }
	result := []byte(stringRecord);	
	
	return shim.Success(result)

}

func main() {

	err := shim.Start(new(SmartContract))
	if err != nil {
		fmt.Printf("Error starting Simple chaincode: %s", err)
	}
}
