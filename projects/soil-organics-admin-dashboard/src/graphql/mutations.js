import { gql } from '@apollo/client';

export const BLOCK_USER = gql`
  mutation BlockUser($email: String!) {
    blockUser(email: $email) {
      email
      blocked
    }
  }
`;

export const UNBLOCK_USER = gql`
  mutation UnblockUser($email: String!) {
    unblockUser(email: $email) {
      email
      blocked
    }
  }
`;
export const CREATE_ITEM = gql`
  mutation CreateItem($name: String!, $description: String, $price: Float!, $type: String!) {
    createItem(name: $name, description: $description, price: $price, type: $type) {
      id
      name
      description
      price
      type
    }
  }
`;

export const UPDATE_ITEM = gql`
  mutation UpdateItem($id: ID!, $name: String, $description: String, $price: Float, $type: String) {
    updateItem(id: $id, name: $name, description: $description, price: $price, type: $type) {
      id
      name
      description
      price
      type
    }
  }
`;

export const DELETE_ITEM = gql`
  mutation DeleteItem($id: ID!) {
    deleteItem(id: $id)
  }
`;

export default { BLOCK_USER, UNBLOCK_USER, CREATE_ITEM, UPDATE_ITEM, DELETE_ITEM};
