package com.example.socialnetworkgui.controller;

import com.example.socialnetworkgui.domain.Message;
import com.example.socialnetworkgui.domain.User;
import com.example.socialnetworkgui.utils.Utils;
import com.example.socialnetworkgui.utils.events.ChangeEventType;
import com.example.socialnetworkgui.utils.events.UserEntityChangeEvent;
import com.example.socialnetworkgui.utils.observer.Observer;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

import java.io.IOException;
import java.util.Objects;
import java.util.Set;

public class FriendPageViewController extends AbstractController implements Observer<UserEntityChangeEvent> {
    private User friend;
    @FXML
    private Label username;
    @FXML
    private ImageView profilePicture;
    @FXML
    private Label aboutMe;
    @FXML
    private Label nrOfFriends;

    public void initialize() {}

    public void setAllViews(User user){
        Image image = new Image(Objects.requireNonNull(getClass().getResourceAsStream(user.getProfilePicture())));
        profilePicture.setImage(image);
        profilePicture.setFitWidth(300);
        profilePicture.setFitHeight(120);
        aboutMe.setText(user.getAboutMe());
        username.setText(user.getUsername());
        Set<User> friends = (Set<User>)getFriendshipService().getAllFriends(user.getId());
        nrOfFriends.setText(String.valueOf(friends.size()));
    }

    @FXML
    public void onBackButtonClick(ActionEvent actionEvent) {
        try {
            FriendsViewController controller = (FriendsViewController) Utils.setSceneOnStage(getStage(),"friends-view.fxml","Friends",440,500);
            Utils.setDataForController(controller, getStage(),getUserService(),getFriendshipService(),getMessageService(),getConectedUser());
            getUserService().removeObserver(this);
        }catch (IOException e){
            e.printStackTrace();
        }
    }

    public void onRemoveFriendButtonClick(ActionEvent actionEvent) {
        getFriendshipService().delete(getConectedUser().getId(), friend.getId());
        MessageAlert.showSuccesMessage(getStage(), "Your friend "+friend.getUsername()+" was succesfully removed");
        onBackButtonClick(actionEvent);
    }

    public void setFriend(User friend) {
        this.friend = friend;
    }

    @Override
    public void afterSetServices() {
        getUserService().addObserver(this);
        setAllViews(friend);
    }

    @Override
    public void update(UserEntityChangeEvent event) {
        if(event.getType() == ChangeEventType.UPDATE){
            if(event.getData().getId().equals(friend.getId())){
                setAllViews(event.getData());
                setFriend(event.getData());
            }
        }
    }
}
