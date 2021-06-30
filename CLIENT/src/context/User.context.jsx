import React,{ createContext,useState } from "react";

const UserContext = createContext({
  isLoggedIn : false,
  id : null,
  pw : null
});

const UserProvider = ({children})=>{
  const [state, setstate] = useState({
    id : null,
    PID : null,
    pw : null,
    ski : null,
    PKi : null,
    PKi_D : null,
    Bi : null,
    Ci : null,
    Di : null,
    Ei : null,
    HPID : null,
    Ri : null,
    zi : null,
    sendId : null,
    rcvId : null,
    Xi : null,
    Xi_D : null,
    CPID : null,
    AUTH : null,
    T1 : null,
    Reqst : null, 
    TID : 0,
    CODE : "3B87084FFCDDDD9B3195D339014AAB09C43B018"
  })
  return (
    <UserContext.Provider value={state}>
      {children}
  	</UserContext.Provider>
  );
}

export {UserProvider};
export default UserContext;
