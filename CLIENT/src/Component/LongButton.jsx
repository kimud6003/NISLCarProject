/* eslint-disable react/prop-types */
import React from 'react';
import PropTypes from 'prop-types';
import styled, { css } from 'styled-components';

const MainButton = styled.button`
  width: 100%;
  height: 3rem;
  border: 1px solid black;
  background-color: #f8f9fa;
  border-radius: 8px;
  margin: 10px;
  ${(props) =>
    props.color &&
    css`
      background-color: ${props.color};
      color: white;
    `}
`;

function LongButton({ color, children }) {
  return (
    <>
      <MainButton props={color}>{children}</MainButton>
    </>
  );
}
MainButton.propTypes = {
  color: PropTypes.string,
  children: PropTypes.string,
};

export default LongButton;
