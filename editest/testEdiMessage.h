//
//  testEdiMessage.h
//  editest
//
//  Created by 徐雷 on 2020/8/7.
//  Copyright © 2020 MailCore. All rights reserved.
//

#ifndef testEdiMessage_h
#define testEdiMessage_h
#include <string>

struct testEdiContact {
    std::string name;
    std::string email;
};

class testEdiAttachment {

public:
    std::string pId;
    std::string messageId;
    std::string filename;
    //string filePath;

    int state;
    int index;
    int retryCount;
    std::string mimeType;
    int partType;     // mailcore::
    int transferEncoding;
    std::string charset;
    std::string partId;
    std::string uniqueId;
    std::string contentId;

    int bodyType;       //0: not body part;  1: plain body part;   2: html body part
    int attachmentType; //0: not attachment; 1: inline attachment; 2: real attachment
    long size;
    std::string refMsgId;
    std::string refAttId;
    long lastUpdated;
};

class testEdiMessage {
public:
    void setFlags(unsigned int flags) {
        this->flags = flags;
        this->isUnread = ((flags & mailcore::MessageFlagSeen) == 0);
        this->isFlagged = ((flags & mailcore::MessageFlagFlagged) > 0);
        this->isAnswered = ((flags & mailcore::MessageFlagAnswered) > 0);
        this->isForwarded = ((flags & mailcore::MessageFlagForwarded) > 0);
        this->isDraft = ((flags & mailcore::MessageFlagDraft) > 0);
        this->isDelete = ((flags & mailcore::MessageFlagDeleted) > 0);
    }
    
    std::string pId;
    std::string accountId;
    std::string folderId;
    std::string folderPath;

    std::string threadPID; //thread primary key

    std::string subject;
    std::string plainBody;
    std::string previewText;
    std::string body;

    std::string messageId;      //gmail message Id or exchange item id
    std::string threadId;       //gmail thread id or exchange conversation id

    long size;

    //int  state;
    long long receivedDate;
    long long date;
    //long long lastUpdated;
    bool needRetry;

    testEdiContact from;
    testEdiContact sender;
    std::vector<testEdiContact> to;
    std::vector<testEdiContact> cc;
    std::vector<testEdiContact> bcc;
    std::vector<testEdiContact> replyTo;

    //gmail only
    std::vector<std::string> labels;

    //refer to RFC 2822, 3.6.4. Identification fields
    std::string headerMessageId;
    std::vector<std::string> inReplyTo;
    std::vector<std::string> references;

    unsigned int flags;
    int attachmentCount;
    //bool hasAttachment;
    bool hasCalendar;
    bool isFlagged;
    bool isUnread;
    bool isAnswered;
    bool isForwarded;
    bool isICalResp;
    bool iCalResp;
    bool isDraft;
    bool isDelete;
    bool inAllMail;
    int isSent;     // 3: has Sent and Inbox label; 1: only has sent label; 0: no sent Label
    std::string smartReply;
    std::string listUnsubscribe;
    std::string listId;
    // Exchange only
    std::string changeKey;
    // IMAP ONLY
    uint32_t uid;

    std::string replyToHeaderMessageId;

//    std::shared_ptr<EdiAttachment> extBody;
    std::vector<std::shared_ptr<testEdiAttachment>> attachmentList;
    //std::map<std::string, std::string> extraHeaders;
    std::string  authResults;
    std::string  DKIMSign;
    std::string  returnPath;
    std::string  xEdisonId;


    int version;

    int category;
    int isJIRA;
    int isZendesk;
};


#endif /* testEdiMessage_h */
