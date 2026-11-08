import React from 'react';
import './Sidebar.css';
import { BsGrid1X2Fill, BsFillArchiveFill, BsFillGrid3X3GapFill, BsPeopleFill, BsListCheck, BsMenuButtonWideFill } from 'react-icons/bs';
import { Link } from 'react-router-dom';

function Sidebar({ openSidebarToggle, OpenSidebar }) {
  return (
    <aside id="sidebar" className={openSidebarToggle ? "sidebar-responsive" : ""}>
      <div className='sidebar-title'>
        <div className='sidebar-brand'>
          <BsFillGrid3X3GapFill className='icon_header' /> SOIL DASHBOARD
        </div>
        <span className='icon close_icon' onClick={OpenSidebar}>X</span>
      </div>

      <ul className='sidebar-list'>
        <li className='sidebar-list-item'>
          <Link to="/">
            <BsGrid1X2Fill className='icon' /> Dashboard
          </Link>
        </li>
        <li className='sidebar-list-item'>
          <Link to="/manage-products">
            <BsFillArchiveFill className='icon' /> Manage Products
          </Link>
        </li>
        <li className='sidebar-list-item'>
          <Link to="/manage-reviews">
            <BsListCheck className='icon' /> Manage Reviews
          </Link>
        </li>
        <li className='sidebar-list-item'>
          <Link to="/manage-customers">
            <BsPeopleFill className='icon' /> Manage Customers
          </Link>
        </li>
      
      </ul>
    </aside>
  );
}

export default Sidebar;
