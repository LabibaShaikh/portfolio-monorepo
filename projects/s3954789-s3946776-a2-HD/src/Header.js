import React from "react";
import './Header.css';
import { BsList } from 'react-icons/bs';
import 
 {BsFillBellFill, BsFillEnvelopeFill, BsPersonCircle, BsSearch, BsJustify}
 from 'react-icons/bs'
function Header(OpenSidebar) {
  return (
    <header className = 'header'>
     <BsList className = 'menu-icon'>
         <BsJustify className = 'icon' onClick = 'OpenSidebar' /> 
        </BsList>
         <div className = 'header-left'>
            
        </div>
        <div className = 'header-right'>
            <BsPersonCircle className = 'icon'/>
        </div>
    
    </header>
  );
}

export default Header;