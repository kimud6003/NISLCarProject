package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"strconv"
	"github.com/hyperledger/fabric/core/chaincode/shim"
	pb "github.com/hyperledger/fabric/protos/peer"
)

type SmartContract struct {}

type Wallet struct {
	ID   string `json:"id"`
	PID   string `json:"pid"`
	PK   string `json:"pki"`
	INFO string `json:"info"`
	LOCATION string `json:"location"`
	Status string `json:"status"`
}

type Car struct {
	Title    string `json:"title"`
	Owner   string `json:"Owner"`
	Price    string `json:"price"`
	Info	string `json:Info`
	Rent   string `json:"Rent"`
	WalletID    string `json:"walletid"`
}

type CarKey struct {
	Key string
	Idx int
}

func (s *SmartContract) Init(APIstub shim.ChaincodeStubInterface) pb.Response {
	return shim.Success(nil)
}

func (s *SmartContract) Invoke(APIstub shim.ChaincodeStubInterface) pb.Response {
	function, args := APIstub.GetFunctionAndParameters()
	
	if function == "initWallet" {
		return s.initWallet(APIstub)
	} else if function == "getWallet" {
		return s.getWallet(APIstub, args)
	}else if function == "setWallet" {
			return s.setWallet(APIstub, args)
	} else if function == "setCar" {
		return s.setCar(APIstub, args)
	} else if function == "getAllCar" {
		return s.getAllCar(APIstub)
	} else if function == "purchaseCar" {
		return s.purchaseCar(APIstub, args)
	}
	fmt.Println("Please check your function : " + function)
	return shim.Error("Unknown function")
}

func (s *SmartContract) initWallet(APIstub shim.ChaincodeStubInterface) pb.Response {

	//Declare wallets
	seller := Wallet{ID: "1Q2W3E4R", Status:""}
	customer := Wallet{ID: "5T6Y7U8", Status:""}

	// Convert seller to []byte
	SellerasJSONBytes, _ := json.Marshal(seller)
	err := APIstub.PutState(seller.ID, SellerasJSONBytes)
	if err != nil {
		return shim.Error("Failed to create asset " + seller.PID)
	}
	// Convert customer to []byte
	CustomerasJSONBytes, _ := json.Marshal(customer)
	err = APIstub.PutState(customer.ID, CustomerasJSONBytes)
	if err != nil {
		return shim.Error("Failed to create asset " + customer.PID)
	}

	return shim.Success(nil)
}

func (s *SmartContract) setWallet(APIstub shim.ChaincodeStubInterface, args []string) pb.Response {
	if len(args) != 2 {
			return shim.Error("Incorrect number of arguments. Expecting 2")
	}
	wallet := Wallet{Name: args[0], ID: args[1], Status:  ""}
	
	WalletasJSONBytes, _ := json.Marshal(wallet)
	err := APIstub.PutState(wallet.ID, WalletasJSONBytes)
	if err != nil {
			return shim.Error("Failed to create asset " + wallet.Name)
	}
	return shim.Success(nil)
}

func (s *SmartContract) getWallet(APIstub shim.ChaincodeStubInterface, args []string) pb.Response {

	walletAsBytes, err := APIstub.GetState(args[0])
	if err != nil {
		fmt.Println(err.Error())
	}

	wallet := Wallet{}
	json.Unmarshal(walletAsBytes, &wallet)

	var buffer bytes.Buffer
	buffer.WriteString("[")
	bArrayMemberAlreadyWritten := false

	if bArrayMemberAlreadyWritten == true {
		buffer.WriteString(",")
	}
	buffer.WriteString("{\"Name\":")
	buffer.WriteString("\"")
	buffer.WriteString(wallet.Name)
	buffer.WriteString("\"")

	buffer.WriteString(", \"ID\":")
	buffer.WriteString("\"")
	buffer.WriteString(wallet.ID)
	buffer.WriteString("\"")

	buffer.WriteString(", \"Status\":")
	buffer.WriteString("\"")
	buffer.WriteString(wallet.Status)
	buffer.WriteString("\"")

	buffer.WriteString("}")
	bArrayMemberAlreadyWritten = true
	buffer.WriteString("]\n")

	return shim.Success(buffer.Bytes())

}



func generateKey(APIstub shim.ChaincodeStubInterface, key string) []byte {
	var isFirst bool = false

	CarkeyAsBytes, err := APIstub.GetState(key)
	if err != nil {
		fmt.Println(err.Error())
	}

	Carkey := CarKey{}
	json.Unmarshal(CarkeyAsBytes, &Carkey)
	var tempIdx string
	tempIdx = strconv.Itoa(Carkey.Idx)
	fmt.Println(Carkey)
	fmt.Println("Key is " + strconv.Itoa(len(Carkey.Key)))
	if len(Carkey.Key) == 0 || Carkey.Key == "" {
		isFirst = true
		Carkey.Key = "MS"
	}
	if !isFirst {
		Carkey.Idx = Carkey.Idx + 1
	}

	fmt.Println("Last CarKey is " + Carkey.Key + " : " + tempIdx)

	returnValueBytes, _ := json.Marshal(Carkey)

	return returnValueBytes
}

func (s *SmartContract) setCar(APIstub shim.ChaincodeStubInterface, args []string) pb.Response {
	if len(args) != 5 {
		return shim.Error("Incorrect number of arguments. Expecting 4")
	}
	
	var Carkey = CarKey{}
	json.Unmarshal(generateKey(APIstub, "latestKey"), &Carkey)
	keyidx := strconv.Itoa(Carkey.Idx)
	fmt.Println("Key : " + Carkey.Key + ", Idx : " + keyidx)

	var Car = Car{Title: args[0], Owner: args[1],Info:args[2], Price:args[3], Rent:"", WalletID: args[4]}
	CarAsJSONBytes, _ := json.Marshal(Car)

	var keyString = Carkey.Key + keyidx
	fmt.Println("Carkey is " + keyString)

	err := APIstub.PutState(keyString, CarAsJSONBytes)
	if err != nil {
		return shim.Error(fmt.Sprintf("Failed to record Car catch: %s", Carkey))
	}

	CarkeyAsBytes, _ := json.Marshal(Carkey)
	APIstub.PutState("latestKey", CarkeyAsBytes)

	return shim.Success(nil)
}

func (s *SmartContract) getAllCar(APIstub shim.ChaincodeStubInterface) pb.Response {
	
	// Find latestKey
	CarkeyAsBytes, _ := APIstub.GetState("latestKey")
	Carkey := CarKey{}
	json.Unmarshal(CarkeyAsBytes, &Carkey)
	idxStr := strconv.Itoa(Carkey.Idx + 1)

	var startKey = "MS0"
	var endKey = Carkey.Key + idxStr
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

func (s *SmartContract) purchaseCar(APIstub shim.ChaincodeStubInterface, args []string) pb.Response {
	// var StatusFromKey, StatusToKey string// Asset holdings
	// var Carprice int // Transaction value
	var err error

	if len(args) != 2 {
		return shim.Error("Incorrect number of arguments. Expecting 2")
	}

	CarAsBytes, err := APIstub.GetState(args[1])
	if err != nil {
		return shim.Error(err.Error())
	}

	Car := Car{}
	json.Unmarshal(CarAsBytes, &Car)
	// Carprice, _ = strconv.Atoi(Car.Price)

	SellerAsBytes, err := APIstub.GetState(Car.WalletID)
	if err != nil {
		return shim.Error("Failed to get state")
	}
	if SellerAsBytes == nil {
		return shim.Error("Entity not found")
	}
	seller := Wallet{}
	json.Unmarshal(SellerAsBytes, &seller)
	// StatusToKey, _ = seller.Status
	// StatusToKey = seller.Status

	CustomerAsBytes, err := APIstub.GetState(args[0])
	if err != nil {
		return shim.Error("Failed to get state")
		var buffer bytes.Buffer
		buffer.WriteString("[")
		bArrayMemberAlreadyWritten := false
	
		if bArrayMemberAlreadyWritten == true {
			buffer.WriteString(",")
		}
		buffer.WriteString("{\"Name\":")
		buffer.WriteString("\"")
		buffer.WriteString(wallet.Name)
		buffer.WriteString("\"")
	
		buffer.WriteString(", \"ID\":")
		buffer.WriteString("\"")
		buffer.WriteString(wallet.ID)
		buffer.WriteString("\"")
	
		buffer.WriteString(", \"Status\":")
		buffer.WriteString("\"")
		buffer.WriteString(wallet.Status)
		buffer.WriteString("\"")
	
		buffer.WriteString("}")
		bArrayMemberAlreadyWritten = true
		
	if CustomerAsBytes == nil {
		return shim.Error("Entity not found")
	}

	customer := Wallet{}
	json.Unmarshal(CustomerAsBytes, &customer)
	// StatusFromKey = customer.Status

	customer.Status =  "Rent " + seller.Name +"Car"
	seller.Status = "Lent "+customer.Name
	updatedCustomerAsBytes, _ := json.Marshal(customer)
	updatedSellerAsBytes, _ := json.Marshal(seller)
	APIstub.PutState(args[0], updatedCustomerAsBytes)
	APIstub.PutState(Car.WalletID, updatedSellerAsBytes)

	// buffer is a JSON array containing QueryResults
	var buffer bytes.Buffer
	buffer.WriteString("[")

	buffer.WriteString("{\"Customer Status\":")
	buffer.WriteString("\"")
	buffer.WriteString(customer.Status)
	buffer.WriteString("\"")

	buffer.WriteString(", \"Seller Status\":")
	buffer.WriteString("\"")
	buffer.WriteString(seller.Status)
	buffer.WriteString("\"")

	buffer.WriteString("}")
	buffer.WriteString("]\n")

	return shim.Success(buffer.Bytes())
}

func main() {

	err := shim.Start(new(SmartContract))
	if err != nil {
		fmt.Printf("Error starting Simple chaincode: %s", err)
	}
}
