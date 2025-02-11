package com.example.socialnetworkgui.controller;

import com.example.socialnetworkgui.domain.Friendship;
import com.example.socialnetworkgui.domain.User;
import com.example.socialnetworkgui.utils.Utils;
import com.example.socialnetworkgui.utils.events.ChangeEventType;
import com.example.socialnetworkgui.utils.events.FriendshipEntityChangeEvent;
import com.example.socialnetworkgui.utils.events.UserEntityChangeEvent;
import com.example.socialnetworkgui.utils.observer.Observer;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import java.io.IOException;
import java.util.Objects;
import java.util.Set;

public class OtherUserPageController extends AbstractController implements Observer<UserEntityChangeEvent> {
    private User otherUser;
    @FXML
    private Label username;
    @FXML
    private ImageView profilePicture;
    @FXML
    private Label aboutMe;
    @FXML
    private Label nrOfFriends;

    public void setAllViews(User user){
        Image image = new Image(Objects.requireNonNull(getClass().getResourceAsStream(otherUser.getProfilePicture())));
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
            AddFriendViewController controller = (AddFriendViewController) Utils.setSceneOnStage(getStage(),"addFriend-view.fxml","AddFriend",480,540);
            Utils.setDataForController(controller, getStage(),getUserService(),getFriendshipService(),getMessageService(),getConectedUser());
            getUserService().removeObserver(this);
        }catch (IOException e){
            e.printStackTrace();
        }
    }

    public void onSendFriendRequestButtonClick(ActionEvent actionEvent) {;
        try {
            getFriendshipService().sendFriendRequest(getConectedUser().getId(), otherUser.getId());
            MessageAlert.showSuccesMessage(getStage(), "Friend request succesfully send to " + otherUser.getUsername());
            onBackButtonClick(actionEvent);
        }catch (Exception e){
            MessageAlert.showErrorMessage(getStage(), e.getMessage());
        }
    }

    public void setOtherUser(User otherUser) {
        this.otherUser = otherUser;
    }

    @Override
    public void afterSetServices() {
        setAllViews(otherUser);
        getUserService().addObserver(this);
    }

    @Override
    public void update(UserEntityChangeEvent event) {
        if (event.getType() == ChangeEventType.UPDATE){
            if(event.getData().getId().equals(otherUser.getId())){
                setOtherUser(event.getData());
                setAllViews(event.getData());
            }
        }
    }
}
