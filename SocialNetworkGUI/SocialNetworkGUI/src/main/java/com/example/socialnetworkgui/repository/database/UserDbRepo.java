package com.example.socialnetworkgui.repository.database;

import com.example.socialnetworkgui.domain.Friendship;
import com.example.socialnetworkgui.domain.User;
import com.example.socialnetworkgui.domain.validation.RepoException;
import com.example.socialnetworkgui.domain.validation.ValidationException;
import com.example.socialnetworkgui.domain.validation.Validator;
import com.example.socialnetworkgui.repository.Repository;
import com.example.socialnetworkgui.repository.Repository2;

import javax.xml.transform.Result;
import java.sql.*;
import java.util.HashSet;
import java.util.List;
import java.util.Optional;
import java.util.Set;
import java.util.function.Predicate;

public class UserDbRepo implements Repository2<Integer,User> {
    private String url;
    private String dbUsername;
    private String dbPassword;
    private Validator<User> validator;

    public UserDbRepo(String url, String username, String password,Validator<User> validator) {
        this.url = url;
        this.dbUsername = username;
        this.dbPassword = password;
        this.validator = validator;
    }

    @Override
    public Optional<User> findOne(Integer integer) {
        Optional<User> opUser = Optional.empty();
        try(Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword);
            PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM \"users\" WHERE id=?")){
            preparedStatement.setInt(1, integer);
            ResultSet result = preparedStatement.executeQuery();
            while(result.next()) {
                int id = result.getInt("id");
                String username = result.getString("username");
                String email = result.getString("email");
                String password = result.getString("password");
                String role = result.getString("role");
                String profilePicture = result.getString("profilePicture");
                String aboutMe = result.getString("aboutMe");
                User user = new User(id, username, email, password, role);
                user.setProfilePicture(profilePicture);
                user.setAboutMe(aboutMe);
                opUser = Optional.of(user);
            }
            result.close();
        }catch (SQLException e){
            e.printStackTrace();
        }
        return opUser;
    }

    public Optional<User> findOne(String username){
        Optional<User> opUser = Optional.empty();
        try(Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword);
            PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM \"users\" WHERE \"username\"=?")){
            preparedStatement.setString(1, username);
            ResultSet result = preparedStatement.executeQuery();
            while(result.next()) {
                int id = result.getInt("id");
                String userName = result.getString("username");
                String email = result.getString("email");
                String password = result.getString("password");
                String role = result.getString("role");
                String profilePicture = result.getString("profilePicture");
                String aboutMe = result.getString("aboutMe");
                User user = new User(id, userName, email, password, role);
                user.setProfilePicture(profilePicture);
                user.setAboutMe(aboutMe);
                opUser = Optional.of(user);
            }
            result.close();
        }catch (SQLException e){
            e.printStackTrace();
        }
        return opUser;
    }

    @Override
    public Iterable<User> findAll() {
        Set<User> users = new HashSet<>();
        try(Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword);
            PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM \"users\"");
            ResultSet resultSet = preparedStatement.executeQuery()){
            while(resultSet.next()){
                int id = resultSet.getInt("id");
                String username = resultSet.getString("username");
                String password = resultSet.getString("password");
                String email = resultSet.getString("email");
                String role = resultSet.getString("role");
                String profilePicture = resultSet.getString("profilePicture");
                String aboutMe = resultSet.getString("aboutMe");
                User user = new User(id, username, email, password, role);
                user.setProfilePicture(profilePicture);
                user.setAboutMe(aboutMe);
                users.add(user);
            }
        }catch(SQLException e){
            e.printStackTrace();
        }
        return users;
    }

    @Override
    public Optional<User> save(User entity) {
        validator.validate(entity);
        Optional<User> opUser = findOne(entity.getUsername());
        if(opUser.isPresent())
            return opUser;
        try(Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword);
            PreparedStatement preparedStatement = connection.prepareStatement("CALL addUser(?,?,?,?)")){
            preparedStatement.setString(1,entity.getUsername());
            preparedStatement.setString(2,entity.getEmail());
            preparedStatement.setString(3,entity.getPassword());
            preparedStatement.setString(4,entity.getRole());
            preparedStatement.executeUpdate();
        }catch (SQLException e){
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Optional<User> delete(Integer id) {
        Optional<User> user = Optional.empty();
        try(Connection connection = DriverManager.getConnection(url,dbUsername,dbPassword);
            PreparedStatement preparedStatement = connection.prepareStatement("DELETE FROM \"users\" WHERE id = ?")){
            preparedStatement.setInt(1,id);
            user = findOne(id);
            if(user.isPresent())
                preparedStatement.executeUpdate();
        }catch (SQLException e){
            e.printStackTrace();
        }
        return user; //empty daca nu exista userul si cu userul daca il sterge
    }

    @Override
    public Optional<User> update(User entity) {
        validator.validate(entity);
        int rez = -1;
        try(Connection connection = DriverManager.getConnection(url,dbUsername,dbPassword);
            PreparedStatement preparedStatement = connection.prepareStatement("UPDATE \"users\" SET username=?,email=?,password=?,role=?,\"profilePicture\"=?,\"aboutMe\"=? WHERE id = ?")){
            preparedStatement.setString(1,entity.getUsername());
            preparedStatement.setString(2,entity.getEmail());
            preparedStatement.setString(3,entity.getPassword());
            preparedStatement.setString(4,entity.getRole());
            preparedStatement.setString(5,entity.getProfilePicture());
            preparedStatement.setString(6,entity.getAboutMe());
            preparedStatement.setInt(7,entity.getId());
            rez = preparedStatement.executeUpdate();
        }catch (SQLException e){
            e.printStackTrace();
        }
        if(rez > 0)
            return Optional.empty();
        return Optional.of(entity);
    }

    @Override
    public int size() {
        try(Connection connection = DriverManager.getConnection(url,dbUsername,dbPassword);
            PreparedStatement preparedStatement = connection.prepareStatement("SELECT COUNT(*) FROM \"users\"");
            ResultSet result = preparedStatement.executeQuery()){
            return result.getInt(1);
        }catch (SQLException e){
            e.printStackTrace();
        }
        return 0;
    }

    public boolean login(String hashPassword, String password) {
        try(Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword);
            PreparedStatement statement = connection.prepareStatement("SELECT md5(?)")){
                statement.setString(1,password);
                ResultSet resultSet = statement.executeQuery();
                resultSet.next();
                return resultSet.getString(1).equals(hashPassword);
        }catch (SQLException e){
            e.printStackTrace();
        }
        return false;
    }
}
