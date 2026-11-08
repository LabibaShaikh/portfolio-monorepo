import React, { useState, useEffect } from 'react';
import { useQuery, useMutation } from '@apollo/client';
import { GET_USERS, UPDATE_USER_BLOCK_STATUS } from './graphql/queries';
import Header from './Header';
import Sidebar from './Sidebar';
import './ManageCustomers.css';
import { format } from 'date-fns';

const ManageCustomers = () => {
  const { loading, error, data } = useQuery(GET_USERS);
  const [updateUserBlockStatus] = useMutation(UPDATE_USER_BLOCK_STATUS);
  const [openSidebarToggle, setOpenSidebarToggle] = useState(false);
  const [users, setUsers] = useState([]);

  const OpenSidebar = () => {
    setOpenSidebarToggle(!openSidebarToggle);
  };

  useEffect(() => {
    if (data) {
      setUsers(data.users);
    }
  }, [data]);

  if (loading) return <p>Loading...</p>;
  if (error) return <p>Error fetching users</p>;

  const handleBlockToggle = (email, currentStatus) => {
    updateUserBlockStatus({ variables: { email, blocked: !currentStatus } })
      .then(() => {
        setUsers(users.map(user => user.email === email ? { ...user, blocked: !currentStatus } : user));
      });
  };

  const isValidDate = (date) => {
    return !isNaN(Date.parse(date));
  };

  const formatDate = (date) => {
    if (isValidDate(date)) {
      return format(new Date(date), 'yyyy-MM-dd');
    }
    return 'Invalid Date';
  };

  return (
    <div className="container">
      <Sidebar openSidebarToggle={openSidebarToggle} OpenSidebar={OpenSidebar} />
      <div className="main-content">
        <Header OpenSidebar={OpenSidebar} />
        <main className="content">
          <h1 className="title">Manage Customers</h1>
          <div className="table-container">
            <table className="table">
              <thead className="table-header">
                <tr>
                  <th>Email</th>
                  <th>First Name</th>
                  <th>Last Name</th>
                  <th>Date of Joining</th>
                  <th>Blocked</th>
                  <th>Actions</th>
                </tr>
              </thead>
              <tbody>
                {users.map((user) => (
                  <tr key={user.email}>
                    <td>{user.email}</td>
                    <td>{user.firstName}</td>
                    <td>{user.lastName}</td>
                    <td>{user.dateOfJoining ? formatDate(user.dateOfJoining) : 'N/A'}</td>
                    <td>{user.blocked ? 'Yes' : 'No'}</td>
                    <td>
                      <button
                        className={`btn ${user.blocked ? 'btn-blocked' : 'btn-unblocked'}`}
                        onClick={() => handleBlockToggle(user.email, user.blocked)}
                      >
                        {user.blocked ? 'Unblock' : 'Block'}
                      </button>
                    </td>
                  </tr>
                ))}
              </tbody>
            </table>
          </div>
        </main>
      </div>
    </div>
  );
};

export default ManageCustomers;
