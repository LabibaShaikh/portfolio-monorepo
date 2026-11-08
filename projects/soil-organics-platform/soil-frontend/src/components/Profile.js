import React, { useState, useEffect } from 'react';
import { useNavigate } from "react-router-dom";
import { format } from "date-fns";
import { validateName, validateEmail, validatePassword } from './Validation';
import { useAuth } from './AuthContext';
import { getProfile, updateProfile, deleteProfile } from '../data/userAPI';

function Profile() {
    const navigate = useNavigate();
    const [profileData, setProfileData] = useState(null);
    const [editMode, setEditMode] = useState(false);
    const [firstName, setFirstName] = useState('');
    const [lastName, setLastName] = useState('');
    const [email, setEmail] = useState('');
    const [newPassword, setNewPassword] = useState('');
    const [confirmPassword, setConfirmPassword] = useState('');
    const [errorMsg, setErrorMsg] = useState('');
    const { logout } = useAuth();

    useEffect(() => {
        const loggedInEmail = localStorage.getItem('loggedInEmail');
        if (loggedInEmail) {
            getProfile(loggedInEmail).then(data => {
                setProfileData(data);
                setFirstName(data.firstName);
                setLastName(data.lastName);
                setEmail(data.email);
            }).catch(error => {
                console.error('Error fetching profile:', error);
                navigate('/SignIn');
            });
        } else {
            navigate('/SignIn');
        }
    }, [navigate]);

    const handleEditToggle = () => {
        setEditMode(!editMode);
        setErrorMsg('');
    };

    const handleSaveChanges = async () => {
        if (!validateName(firstName) || !validateName(lastName) || !validateEmail(email) || (newPassword && !validatePassword(newPassword))) {
            setErrorMsg('Please ensure all fields are valid.');
            return;
        }

        if (newPassword && newPassword === profileData.password) {
            setErrorMsg('New password must be different from the current password.');
            return;
        }

        if (newPassword !== confirmPassword) {
            setErrorMsg('Passwords do not match.');
            return;
        }

        try {
            const updatedProfile = {
                firstName,
                lastName,
                email,
                password: newPassword.trim() ? newPassword : undefined
            };

            const response = await updateProfile(email, updatedProfile);
            setProfileData(response.user);
            setEditMode(false);
            setErrorMsg('');
            alert('Profile updated successfully.');
        } catch (error) {
            console.error('Error updating profile:', error);
            setErrorMsg('Failed to update profile.');
        }
    };

    const handleDeleteProfile = async () => {
        if (window.confirm('Are you sure you want to delete your profile? This action cannot be undone.')) {
            try {
                await deleteProfile(email);
                logout();
                navigate('/');
            } catch (error) {
                console.error('Error deleting profile:', error);
                setErrorMsg('Failed to delete profile.');
            }
        }
    };

    const handleSignOut = () => {
        logout();
        navigate('/');
    };

    if (!profileData) {
        return <p>No profile data found.</p>;
    }

    const formattedDate = profileData.dateOfJoining ? format(new Date(profileData.dateOfJoining), 'yyyy-MM-dd') : 'N/A';

    return (
        <div className='container'>
            <h1>Welcome {firstName}!</h1>
            <div className='header'>
                <h1>User Profile</h1>
                <div className="underline"></div>
            </div>
            {editMode ? (
                <div className='inputs'>
                    <label>First Name:</label>
                    <input type="text" value={firstName} onChange={e => setFirstName(e.target.value)} />
                    <label>Last Name:</label>
                    <input type="text" value={lastName} onChange={e => setLastName(e.target.value)} />
                    <label>Email:</label>
                    <input type="email" value={email} onChange={e => setEmail(e.target.value)} />
                    <label>New Password:</label>
                    <input type="password" value={newPassword} onChange={e => setNewPassword(e.target.value)} />
                    <label>Confirm New Password:</label>
                    <input type="password" value={confirmPassword} onChange={e => setConfirmPassword(e.target.value)} />
                    <div className="submit-container">
                        <button className="submit" onClick={handleSaveChanges}>Save Changes</button>
                        <button className="submit gray" onClick={handleEditToggle}>Cancel</button>
                    </div>
                    {errorMsg && <p>{errorMsg}</p>}
                </div>
            ) : (
                <div className='profile-details'>
                    <div className='profile-info'><span>First Name:</span> {profileData.firstName}</div>
                    <div className='profile-info'><span>Last Name:</span> {profileData.lastName}</div>
                    <div className='profile-info'><span>Email:</span> {profileData.email}</div>
                    <div className='profile-info'><span>Date of Joining:</span> {formattedDate}</div>
                    <div className="submit-container">
                        <button className="submit" onClick={handleEditToggle}>Edit Profile</button>
                        <button className="submit gray" onClick={handleDeleteProfile}>Delete Profile</button>
                        <button className="submit gray" onClick={handleSignOut}>Sign Out</button>
                    </div>
                </div>
            )}
        </div>
    );
}

export default Profile;
