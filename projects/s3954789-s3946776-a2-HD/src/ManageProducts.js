import React, { useState, useEffect } from 'react';
import { useQuery, useMutation } from '@apollo/client';
import { GET_ITEMS, CREATE_ITEM, UPDATE_ITEM, DELETE_ITEM } from './graphql/queries';
import Header from './Header';
import Sidebar from './Sidebar';
import './ManageProducts.css';

const ManageProducts = () => {
  const { loading, error, data } = useQuery(GET_ITEMS);
  const [createItem] = useMutation(CREATE_ITEM, {
    refetchQueries: [{ query: GET_ITEMS }]
  });
  const [updateItem] = useMutation(UPDATE_ITEM, {
    refetchQueries: [{ query: GET_ITEMS }]
  });
  const [deleteItem] = useMutation(DELETE_ITEM, {
    refetchQueries: [{ query: GET_ITEMS }]
  });
  const [openSidebarToggle, setOpenSidebarToggle] = useState(false);
  const [items, setItems] = useState([]);
  const [newItem, setNewItem] = useState({ prodName: '', price: 0, qty: 0, onSale: false, imgPath: '' });
  const [editingItem, setEditingItem] = useState(null);

  const OpenSidebar = () => {
    setOpenSidebarToggle(!openSidebarToggle);
  };

  useEffect(() => {
    if (data) {
      setItems(data.items);
    }
  }, [data]);

  if (loading) return <p>Loading...</p>;
  if (error) return <p>Error fetching items</p>;

  const handleCreateItem = () => {
    createItem({ variables: { ...newItem } });
    setNewItem({ prodName: '', price: 0, qty: 0, onSale: false, imgPath: '' });
  };

  const handleUpdateItem = () => {
    updateItem({ variables: { ...editingItem } });
    setEditingItem(null);
  };

  const handleDeleteItem = (id) => {
    deleteItem({ variables: { id } });
  };

  const startEditing = (item) => {
    setEditingItem(item);
  };

  return (
    <div className="container">
      <Sidebar openSidebarToggle={openSidebarToggle} OpenSidebar={OpenSidebar} />
      <div className="main-content">
        <Header OpenSidebar={OpenSidebar} />
        <main className="content">
          <h1 className="title">Manage Products</h1>
          <div className="table-container">
            <table className="table">
              <thead className="table-header">
                <tr>
                  <th>ID</th>
                  <th>Name</th>
                  <th>Price</th>
                  <th>Quantity</th>
                  <th>On Sale</th>
                  <th>Image Path</th>
                  <th>Actions</th>
                </tr>
              </thead>
              <tbody>
                {items.map((item) => (
                  <tr key={item.id}>
                    <td>{item.id}</td>
                    <td>{item.prodName}</td>
                    <td>{item.price}</td>
                    <td>{item.qty}</td>
                    <td>{item.onSale ? 'Yes' : 'No'}</td>
                    <td>{item.imgPath}</td>
                    <td>
                      <button className="btn btn-edit" onClick={() => startEditing(item)}>Edit</button>
                      <button className="btn btn-delete" onClick={() => handleDeleteItem(item.id)}>Delete</button>
                    </td>
                  </tr>
                ))}
              </tbody>
            </table>
          </div>
          <div className="form-container">
            {editingItem ? (
              <div>
                <h2>Edit Item</h2>
                <input type="text" value={editingItem.prodName} onChange={(e) => setEditingItem({ ...editingItem, prodName: e.target.value })} placeholder="Name" />
                <input type="number" value={editingItem.price} onChange={(e) => setEditingItem({ ...editingItem, price: parseFloat(e.target.value) })} placeholder="Price" />
                <input type="number" value={editingItem.qty} onChange={(e) => setEditingItem({ ...editingItem, qty: parseInt(e.target.value) })} placeholder="Quantity" />
                <input type="text" value={editingItem.imgPath} onChange={(e) => setEditingItem({ ...editingItem, imgPath: e.target.value })} placeholder="Image Path" />
                <label>
                  <input type="checkbox" checked={editingItem.onSale} onChange={(e) => setEditingItem({ ...editingItem, onSale: e.target.checked })} /> On Sale
                </label>
                <button className="btn btn-save" onClick={handleUpdateItem}>Save</button>
                <button className="btn btn-cancel" onClick={() => setEditingItem(null)}>Cancel</button>
              </div>
            ) : (
              <div>
                <h2>Add New Item</h2>
                <input type="text" value={newItem.prodName} onChange={(e) => setNewItem({ ...newItem, prodName: e.target.value })} placeholder="Name" />
                <input type="number" value={newItem.price} onChange={(e) => setNewItem({ ...newItem, price: parseFloat(e.target.value) })} placeholder="Price" />
                <input type="number" value={newItem.qty} onChange={(e) => setNewItem({ ...newItem, qty: parseInt(e.target.value) })} placeholder="Quantity" />
                <input type="text" value={newItem.imgPath} onChange={(e) => setNewItem({ ...newItem, imgPath: e.target.value })} placeholder="Image Path" />
                <label>
                  <input type="checkbox" checked={newItem.onSale} onChange={(e) => setNewItem({ ...newItem, onSale: e.target.checked })} /> On Sale
                </label>
                <button className="btn btn-add" onClick={handleCreateItem}>Add Item</button>
              </div>
            )}
          </div>
        </main>
      </div>
    </div>
  );
};

export default ManageProducts;
