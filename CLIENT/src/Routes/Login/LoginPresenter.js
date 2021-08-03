import React from 'react'
import styled,{css}from 'styled-components'
const Background = styled.div`
    width:100vw;
    height:85vh;
    background-color:black;

`

const BottomBlock = styled.div`
    display:flex;
    justify-content:center;
    position:absolute;
    width:100%;
    bottom:0;
    padding-bottom:10px;
    button{
        margin: 20px;
    }
`;

const LoginButton = styled.button`
    font-size: 1rem;   
    width:10rem;
    height:3rem;
    border-radius:4px;
    border-color:black;
    background-color : white;
    color:black;

    ${props =>
    props.signup&&
    css`
      background-color : black;
      color: white;
    `}
`;


function LoginPresenter() {
    return (
        <>
            <Background/>
            <BottomBlock>
                <LoginButton>
                    Log In
                </LoginButton>
                <LoginButton signup={true}>
                    Sign Up
                </LoginButton>
            </BottomBlock>
        </>
    )
}

export default LoginPresenter


