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
import java.util.ArrayList;
import java.util.List;
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
            if(ok && isChange) {
                MessageAlert.showSuccesMessage(getStage(), "User data successfully updated");
                onBackBottonClick(actionEvent);
            }
            else if(ok)
                MessageAlert.showErrorMessage(getStage(), "No changes detected");
        }catch (ValidationException | RepoException | ServiceException e) {
            MessageAlert.showErrorMessage(getStage(), e.getMessage());
        }
    }

    public void onBackBottonClick(ActionEvent actionEvent) {
        try{
            AbstractController controller = Utils.setSceneOnStage(getStage(),"myPage-view.fxml","MyPage",525,428);
            Utils.setDataForController(controller,getStage(),getUserService(),getFriendshipService(),getMessageService(),getConectedUser());
        }catch (IOException e) {
            e.printStackTrace();
        }
    }

    public List<Image> createAvatarsImages(){
        Image avatar1 = new Image(Objects.requireNonNull(getClass().getResourceAsStream("/images/avatars/avatar1.png")));
        Image avatar2 = new Image(Objects.requireNonNull(getClass().getResourceAsStream("/images/avatars/avatar2.png")));
        Image avatar3 = new Image(Objects.requireNonNull(getClass().getResourceAsStream("/images/avatars/avatar3.png")));
        Image avatar4 = new Image(Objects.requireNonNull(getClass().getResourceAsStream("/images/avatars/avatar4.png")));
        Image avatar5 = new Image(Objects.requireNonNull(getClass().getResourceAsStream("/images/avatars/avatar5.png")));
        Image avatar6 = new Image(Objects.requireNonNull(getClass().getResourceAsStream("/images/avatars/avatar6.png")));
        List<Image> images = new ArrayList<>();
        images.add(avatar1);
        images.add(avatar2);
        images.add(avatar3);
        images.add(avatar4);
        images.add(avatar5);
        images.add(avatar6);
        return images;
    }

    public List<ImageView> createIageViews(List<Image> images){
        List<ImageView> imageViews = new ArrayList<>();
        images.forEach(image -> {imageViews.add(new ImageView(image));});
        return imageViews;
    }

    public void setWidthHeightForImageViews(List<ImageView> imageViews, double width, double height){
        imageViews.forEach(image -> {image.setFitWidth(width);image.setFitHeight(height);});
    }

    public List<Label> createNumberLabels(){
        List<Label> labels = new ArrayList<>();
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
        labels.add(nr1);
        labels.add(nr2);
        labels.add(nr3);
        labels.add(nr4);
        labels.add(nr5);
        labels.add(nr6);
        return labels;
    }

    public void loadAvatars(){
        List<Image> images = createAvatarsImages();
        List<ImageView> imageViews = createIageViews(images);
        setWidthHeightForImageViews(imageViews,180,200);
        List<Label> numberLabels = createNumberLabels();
        for(int i=0;i<numberLabels.size();i+=2){
            model.add(new HBox(numberLabels.get(i),imageViews.get(i),imageViews.get(i+1),numberLabels.get(i+1)));
        }
    }

    @Override
    public void afterSetServices() {
        loadAvatars();
    }
}
