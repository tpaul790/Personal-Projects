package com.example.socialnetworkgui.controller;

import com.example.socialnetworkgui.domain.Tuple;
import com.example.socialnetworkgui.domain.validation.RepoException;
import com.example.socialnetworkgui.domain.validation.ServiceException;
import com.example.socialnetworkgui.domain.validation.ValidationException;
import com.example.socialnetworkgui.utils.Utils;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.HBox;

import java.io.IOException;
import java.util.Objects;

public class UpdateUserDataViewController extends AbstractController {
    private ObservableList<HBox> model = FXCollections.observableArrayList();

    @FXML
    private RadioButton maleCheck;
    @FXML
    private RadioButton femaleCheck;
    @FXML
    private ListView<HBox> avatarList = new ListView<>();
    @FXML
    private TextArea aboutMe;

    public void initialize() {
        avatarList.setCellFactory(lv -> new ListCell<>() {
            @Override
            protected void updateItem(HBox item, boolean empty) {
                super.updateItem(item, empty);
                if (empty || item == null) {
                    setGraphic(null);
                } else {
                    System.out.println("HBox structura: " + item.getChildren());
                    setGraphic(item);
                }
            }
        });
        avatarList.setItems(model);
        maleCheck.selectedProperty().addListener((observable, oldValue, newValue) -> {
            femaleCheck.setDisable(newValue);
        });
        femaleCheck.selectedProperty().addListener((observable, oldValue, newValue) -> {
            maleCheck.setDisable(newValue);
        });
    }

    public void onSaveButtonClick(ActionEvent actionEvent) {
        String aboutMeText = aboutMe.getText();
        boolean ok = true;
        boolean isChange = false;
        try {
            HBox hbox = avatarList.getSelectionModel().getSelectedItem();
            if (!aboutMeText.isEmpty()) {
                getConectedUser().setAboutMe(aboutMeText);
                isChange = true;
            }
            if (hbox != null) {
                if(!maleCheck.isSelected() && !femaleCheck.isSelected()) {
                    MessageAlert.showErrorMessage(getStage(),"You should say if you want the male avatar or the female one by checking the male/female radio button");
                    ok = false;
                }else{
                    String newProfile = "/images/avatars/avatar";
                    if(maleCheck.isSelected()) {
                        Label label = (Label)hbox.getChildren().getFirst();
                        newProfile = newProfile + label.getText();
                    }else{
                        Label label = (Label)hbox.getChildren().getLast();
                        newProfile = newProfile + label.getText();
                    }
                    newProfile = newProfile+".png";
                    System.out.println(newProfile);
                    getConectedUser().setProfilePicture(newProfile);
                    isChange = true;
                }
            }
            if(isChange)
                getUserService().update(getConectedUser());
            if(ok && isChange)
                MessageAlert.showSuccesMessage(getStage(), "User data successfully updated");
            else if(ok)
                MessageAlert.showErrorMessage(getStage(), "No changes detected");
        }catch (ValidationException | RepoException | ServiceException e) {
            MessageAlert.showErrorMessage(getStage(), e.getMessage());
        }
    }

    public void onBackBottonClick(ActionEvent actionEvent) {
        try{
            AbstractController controller = Utils.setSceneOnStage(getStage(),"myPage-view.fxml","Settings",525,428);
            Utils.setDataForController(controller,getStage(),getUserService(),getFriendshipService(),getMessageService(),getConectedUser());
        }catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void loadAvatars(){
        Image avatar1 = new Image(Objects.requireNonNull(getClass().getResourceAsStream("/images/avatars/avatar1.png")));
        Image avatar2 = new Image(Objects.requireNonNull(getClass().getResourceAsStream("/images/avatars/avatar2.png")));
        Image avatar3 = new Image(Objects.requireNonNull(getClass().getResourceAsStream("/images/avatars/avatar3.png")));
        Image avatar4 = new Image(Objects.requireNonNull(getClass().getResourceAsStream("/images/avatars/avatar4.png")));
        Image avatar5 = new Image(Objects.requireNonNull(getClass().getResourceAsStream("/images/avatars/avatar5.png")));
        Image avatar6 = new Image(Objects.requireNonNull(getClass().getResourceAsStream("/images/avatars/avatar6.png")));
        ImageView view1 = new ImageView(avatar1);
        ImageView view2 = new ImageView(avatar2);
        ImageView view3 = new ImageView(avatar3);
        ImageView view4 = new ImageView(avatar4);
        ImageView view5 = new ImageView(avatar5);
        ImageView view6 = new ImageView(avatar6);
        view1.setFitWidth(180);
        view2.setFitWidth(180);
        view3.setFitWidth(180);
        view4.setFitWidth(180);
        view5.setFitWidth(180);
        view6.setFitWidth(180);
        view1.setFitHeight(200);
        view2.setFitHeight(200);
        view3.setFitHeight(200);
        view4.setFitHeight(200);
        view5.setFitHeight(200);
        view6.setFitHeight(200);
        Label nr1 = new Label();
        nr1.setText(Integer.toString(1));
        Label nr2 = new Label();
        nr2.setText(Integer.toString(2));
        Label nr3 = new Label();
        nr3.setText(Integer.toString(3));
        Label nr4 = new Label();
        nr4.setText(Integer.toString(4));
        Label nr5 = new Label();
        nr5.setText(Integer.toString(5));
        Label nr6 = new Label();
        nr6.setText(Integer.toString(6));
        HBox hbox1 = new HBox(nr1,view1,view2,nr2);
        HBox hbox2 = new HBox(nr3,view3,view4,nr4);
        HBox hbox3 = new HBox(nr5,view5,view6,nr6);
        model.add(hbox1);
        model.add(hbox2);
        model.add(hbox3);
    }

    @Override
    public void afterSetServices() {
        loadAvatars();
    }
}
